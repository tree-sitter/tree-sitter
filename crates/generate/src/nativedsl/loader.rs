//! Module system and glue code for the native DSL pipeline.

use std::path::{Path, PathBuf};

use crate::{
    IoError,
    nativedsl::{
        DisallowedItemKind, DocumentId, DocumentMap, DocumentSpan, DslError, DslResult,
        ImportedRule, LexError, LexErrorKind, LowerError, LowerErrorKind, LoweringState,
        MAX_MODULE_DEPTH, Module, ModuleError, ModuleId, ModuleIdSet, NoteMessage, ResolveError,
        TypeError, TypeErrorKind,
        apply_cfg::{CfgEnvId, CfgState, apply_cfg},
        ast::{IdentKind, ModuleContext, Node, NodeId, SharedAst, Span},
        expand_macro_calls, lexer, lower, parser,
        resolve::{self, ResolveErrorKind},
        typecheck::{self, TypeEnv},
    },
    rules::RulePool,
    strpool::StrId,
};

/// Mutable pipeline state passed through the load/lower recursion.
pub struct Loader<'a> {
    shared: &'a mut SharedAst,
    modules: &'a mut Vec<Module>,
    env: &'a mut TypeEnv,
    state: &'a mut LoweringState,
    pool: &'a mut RulePool,
    cfg: &'a mut CfgState,
    documents: &'a mut DocumentMap,
    ancestor_documents: Vec<DocumentId>,
    /// Module dedup cache keyed by canonical path, kind, and cfg environment.
    loaded: Vec<LoadedModuleRef>,
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub(super) enum ModuleKind {
    /// Grammar file (root or inherited). Must have grammar block, may have rules.
    Grammar,
    /// Library file (imported). Anything except a grammar block or override rule.
    Library,
}

/// A reference to a module loaded into [`Loader::modules`].
struct LoadedModuleRef {
    document: DocumentId,
    kind: ModuleKind,
    cfg_env: CfgEnvId,
    /// Index into the global [`Loader::modules`] table.
    gid: ModuleId,
}

impl<'a> Loader<'a> {
    pub const fn new(
        shared: &'a mut SharedAst,
        modules: &'a mut Vec<Module>,
        env: &'a mut TypeEnv,
        state: &'a mut LoweringState,
        pool: &'a mut RulePool,
        cfg: &'a mut CfgState,
        documents: &'a mut DocumentMap,
    ) -> Self {
        Self {
            shared,
            modules,
            env,
            state,
            pool,
            cfg,
            documents,
            ancestor_documents: Vec::new(),
            loaded: Vec::new(),
        }
    }

    /// Load a root tsg grammar module.
    ///
    /// # Errors
    ///
    /// Returns `Err` if the module isn't valid tsg source.
    pub fn load_root(mut self, source: &str, path: &Path) -> DslResult<()> {
        let canonical = dunce::canonicalize(path).map_err(|error| {
            let document = self.documents.insert(path.to_owned(), source.to_string());
            LowerError::without_span(
                LowerErrorKind::ModuleResolveFailed(IoError {
                    error,
                    path: Some(path.to_path_buf()),
                }),
                document,
            )
        })?;
        let document = self.documents.insert(canonical, source.to_string());
        self.ancestor_documents.push(document);
        _ = self.load_module(document, ModuleKind::Grammar)?;
        Ok(())
    }

    fn load_module(&mut self, document: DocumentId, kind: ModuleKind) -> DslResult<ModuleId> {
        let source_document = self.documents.document(document);
        let source = source_document.text();

        if source.len() > u32::MAX as usize {
            Err(LexError::without_span(
                LexErrorKind::InputTooLarge,
                document,
            ))?;
        }

        // The root's capacity is seeded by `parse_native_dsl`. Reserve here for children.
        if self.ancestor_documents.len() > 1 {
            self.shared.reserve_for_module(source.len());
        }

        let tokens = lexer::Lexer::new(source_document).tokenize()?;
        let mut ctx =
            parser::Parser::new(&tokens, source_document, self.shared, self.pool.strs_mut())
                .parse()?;

        // Merge this module's flags into the current environment. Existing values
        // win, so parent declarations override child declarations.
        self.cfg
            .merge_module_flags(self.shared, &mut ctx, source, self.pool.strs())?;

        // Apply cfg gating *before* loading children so cfg-disabled imports aren't evaluated.
        if ctx.has_cfg {
            apply_cfg(self.shared, &mut ctx, self.pool.strs(), self.cfg, kind)?;
        }

        match kind {
            ModuleKind::Grammar => self.validate_grammar(&ctx)?,
            ModuleKind::Library => self.validate_import_items(&ctx)?,
        }

        // Inline top-level rule-set macro invocations into `ExpandedRule` decls.
        // Runs before child loads so this module's nodes all sit in one contiguous
        // arena range.
        expand_macro_calls::expand_macro_calls(self.shared, self.pool.strs_mut(), &mut ctx)?;
        ctx.set_node_end(self.shared.arena.next_id());

        self.load_children(&ctx)?;

        // Child loading is complete, so this module's final table index is fixed.
        let global_id = ModuleId::from_index(self.modules.len())
            .ok_or_else(|| LowerError::without_span(LowerErrorKind::ModuleTooMany, document))?;

        // Flatten the transitive library imports once
        let imported_rules =
            super::collect_imported_rules(&self.shared.arena, &ctx.module_refs, self.modules);

        self.resolve_current_module(&mut ctx, global_id, &imported_rules)?;

        // Child modules already populated `self.env` during their own `load_module` calls.
        let source = self.documents.document(document).text();
        typecheck::check(self.shared, &ctx, source, self.env, self.pool.strs())
            .map_err(|e| self.enrich_type_error(&ctx, e))?;
        let module = match kind {
            ModuleKind::Grammar => {
                let lowered = Box::new(lower::lower_grammar(
                    self.state,
                    self.pool,
                    self.shared,
                    self.modules,
                    self.documents,
                    &ctx,
                    &imported_rules,
                )?);
                let exports = super::build_exports(
                    self.shared,
                    &ctx,
                    self.pool,
                    &lowered.variables,
                    &lowered.external_roots,
                );
                Module::Grammar {
                    ctx,
                    lowered,
                    exports,
                }
            }
            ModuleKind::Library => {
                let lowered_rules = lower::lower_library(
                    self.state,
                    self.pool,
                    self.shared,
                    self.modules,
                    self.documents,
                    &ctx,
                )?;
                let exports =
                    super::build_exports(self.shared, &ctx, self.pool, &lowered_rules, &[]);
                Module::Library {
                    ctx,
                    lowered_rules,
                    exports,
                }
            }
        };
        debug_assert_eq!(usize::from(global_id), self.modules.len());
        self.modules.push(module);

        Ok(global_id)
    }

    fn resolve_current_module(
        &mut self,
        ctx: &mut ModuleContext,
        global_id: ModuleId,
        imported_rules: &[ImportedRule],
    ) -> DslResult<()> {
        let base = ctx
            .inherit_module(&self.shared.arena)
            .and_then(|(idx, span)| self.modules[usize::from(idx)].lowered().map(|g| (g, span)));

        let mut collected =
            resolve::collect_decls(self.shared, ctx, self.pool, base, imported_rules, global_id)
                .map_err(|e| self.enrich_resolve_error(ctx, e))?;
        if collected.has_qualified_calls() {
            resolve::resolve_qualified_call_targets(
                self.shared,
                ctx,
                self.pool,
                self.modules,
                &mut collected,
            )
            .map_err(|e| self.enrich_resolve_error(ctx, e))?;
            ctx.start_late_nodes(self.shared.arena.next_id());
            expand_macro_calls::expand_qualified_macro_calls(
                self.shared,
                self.pool.strs_mut(),
                ctx,
                self.modules,
                collected.qualified_calls(),
            )?;
            ctx.set_late_node_end(self.shared.arena.next_id());
            resolve::register_expanded_decls(&mut collected, self.shared, self.pool.strs(), ctx)
                .map_err(|e| self.enrich_resolve_error(ctx, e))?;
        }
        resolve::finish_decls(
            &mut collected,
            self.shared,
            ctx,
            self.pool,
            base,
            imported_rules,
        )
        .map_err(|e| self.enrich_resolve_error(ctx, e))?;
        resolve::resolve_with_decls(self.shared, ctx, self.pool, self.modules, &collected)
            .map_err(|e| self.enrich_resolve_error(ctx, e))?;
        Ok(())
    }

    fn load_child_module(
        &mut self,
        parent_document: DocumentId,
        module_path: &Path,
        span: Span,
        kind: ModuleKind,
    ) -> DslResult<ModuleId> {
        let cfg_env = self.cfg.env_id();
        let existing_document = self.documents.id_for_path(module_path);

        if let Some(document) = existing_document
            && let Some(module_ref) = self.loaded.iter().find(|module| {
                module.document == document && module.kind == kind && module.cfg_env == cfg_env
            })
        {
            return Ok(module_ref.gid);
        }

        if self.ancestor_documents.len() >= MAX_MODULE_DEPTH {
            return Err(LowerError::new(
                LowerErrorKind::ModuleDepthExceeded,
                parent_document,
                span,
            )
            .into());
        }

        let document = if let Some(document) = existing_document {
            document
        } else {
            let source = std::fs::read_to_string(module_path).map_err(|error| {
                LowerError::new(
                    LowerErrorKind::ModuleReadFailed(IoError {
                        error,
                        path: Some(module_path.to_path_buf()),
                    }),
                    parent_document,
                    span,
                )
            })?;
            self.documents.insert(module_path.to_path_buf(), source)
        };

        if self.ancestor_documents.contains(&document) {
            return Err(ModuleError::new(
                LowerError::without_span(LowerErrorKind::ModuleCycle, document).into(),
                DocumentSpan::new(parent_document, span),
            )
            .into());
        }

        self.ancestor_documents.push(document);
        let checkpoint = self.cfg.checkpoint();
        let result = self
            .load_module(document, kind)
            .map_err(|inner| ModuleError::new(inner, DocumentSpan::new(parent_document, span)));
        self.cfg.restore(checkpoint);
        self.ancestor_documents.pop();

        let gid = result?;
        self.loaded.push(LoadedModuleRef {
            document,
            kind,
            cfg_env,
            gid,
        });
        Ok(gid)
    }

    /// Resolve `Import` and `Inherit` nodes, loading each child file.
    fn load_children(&mut self, ctx: &ModuleContext) -> Result<(), DslError> {
        for &node_id in &ctx.module_refs {
            let (kind, &path) = match self.shared.arena.get(node_id) {
                Node::Inherit { path, module: None } => (ModuleKind::Grammar, path),
                Node::Import { path, module: None } => (ModuleKind::Library, path),
                Node::Inherit {
                    module: Some(_), ..
                }
                | Node::Import {
                    module: Some(_), ..
                } => continue, // Already resolved
                _ => unreachable!(),
            };

            let source_document = self.documents.document(ctx.document);
            let candidate = source_document
                .path()
                .parent()
                .unwrap()
                .join(path.resolve(source_document.text()));
            let canonical = resolve_path(&candidate, ctx.document, path)?;
            let gid = self.load_child_module(ctx.document, &canonical, path, kind)?;

            expect_pat!(
                (Node::Inherit { module, .. } | Node::Import { module, .. }),
                self.shared.arena.get_mut(node_id)
            );
            *module = Some(gid);
        }

        Ok(())
    }

    /// Validate that grammar block exists and structural constraints on `inherit()` calls
    fn validate_grammar(&self, ctx: &ModuleContext) -> DslResult<()> {
        let Some(config) = ctx.grammar_config.as_ref() else {
            return Err(LowerError::without_span(
                LowerErrorKind::MissingGrammarBlock,
                ctx.document,
            )
            .into());
        };
        if config.language.is_none() {
            let block = ctx
                .root_items
                .iter()
                .find(|&&id| matches!(self.shared.arena.get(id), Node::Grammar))
                .unwrap();
            Err(LowerError::new(
                LowerErrorKind::MissingLanguageField,
                ctx.document,
                self.shared.arena.span(*block),
            ))?;
        }
        let inherits = ctx.inherits(&self.shared.arena).collect::<Vec<_>>();
        if let [first, second, rest @ ..] = inherits.as_slice() {
            let mut err = LowerError::with_note(
                LowerErrorKind::MultipleInherits,
                ctx.document,
                self.shared.arena.span(*second),
                ctx.note(
                    NoteMessage::FirstDefinedHere,
                    self.shared.arena.span(*first),
                ),
            );
            for &extra in rest {
                err.add_note(ctx.note(
                    NoteMessage::AlsoInheritedHere,
                    self.shared.arena.span(extra),
                ));
            }
            Err(err)?;
        }

        // `inherit()` exists but no `inherits` in grammar config
        if let Some(&inherit_ref) = inherits.first()
            && config.inherits.is_none()
        {
            Err(LowerError::new(
                LowerErrorKind::InheritWithoutConfig,
                ctx.document,
                self.shared.arena.span(inherit_ref),
            ))?;
        }

        Ok(())
    }

    /// Validate that an `import`ed file only contains allowed items (No grammar
    /// block, `override` rules, or `inherit` calls).
    fn validate_import_items(&self, ctx: &ModuleContext) -> DslResult<()> {
        if let Some(inherit_id) = ctx.inherits(&self.shared.arena).next() {
            Err(LowerError::new(
                LowerErrorKind::ModuleDisallowedItem(DisallowedItemKind::Inherit),
                ctx.document,
                self.shared.arena.span(inherit_id),
            ))?;
        }
        for &item_id in &ctx.root_items {
            let kind = match self.shared.arena.get(item_id) {
                Node::Grammar => DisallowedItemKind::GrammarBlock,
                Node::Rule {
                    is_override: true, ..
                } => DisallowedItemKind::OverrideRule,
                _ => continue,
            };
            Err(LowerError::new(
                LowerErrorKind::ModuleDisallowedItem(kind),
                ctx.document,
                self.shared.arena.span(item_id),
            ))?;
        }
        Ok(())
    }

    /// If `e` is `UnknownIdentifier(name)` and `name` matches a cfg-dropped declaration,
    /// attach a note pointing at the gated decl with the cfg flag name.
    fn enrich_resolve_error(&self, current: &ModuleContext, mut e: ResolveError) -> ResolveError {
        let ResolveErrorKind::UnknownIdentifier(name) = &e.kind else {
            return e;
        };
        let Some(name_id) = self.pool.strs().get(name) else {
            return e;
        };
        let Some((cfg_id, owner)) = self.find_cfg_drop(current, name_id) else {
            return e;
        };
        expect_pat!(Node::Cfg { name: flag, .. }, *self.shared.arena.get(cfg_id));
        let flag_name = self.pool.strs().resolve(flag).to_string();
        let decl_span = self.shared.arena.span(cfg_id);
        e.add_note(owner.note(NoteMessage::GatedByDisabledCfg(flag_name), decl_span));
        e
    }

    fn enrich_type_error(&self, current: &ModuleContext, e: TypeError) -> TypeError {
        match e.kind {
            TypeErrorKind::UndefinedMacro(_) => self.note_undefined_macro(current, e),
            TypeErrorKind::ArgCountMismatch { .. }
            | TypeErrorKind::TypeMismatch { .. }
            | TypeErrorKind::ConstraintMismatch { .. } => self.note_macro_definition(current, e),
            _ => e,
        }
    }

    /// Point at the macro whose signature the call violated. The parameter list
    /// that rejected the call is not visible from the call site, and for an
    /// imported macro it is not even in the same file.
    fn note_macro_definition(&self, current: &ModuleContext, mut e: TypeError) -> TypeError {
        let Some(span) = e.span else {
            return e;
        };
        let arena = &self.shared.arena;
        let Some(macro_id) = current.iter_own_nodes(arena).find_map(|(id, node)| {
            let Node::Call { name, args } = *node else {
                return None;
            };
            let Node::Ident(IdentKind::Macro(macro_id)) = *arena.get(name) else {
                return None;
            };
            // An arity error spans the call, an argument error spans the argument.
            let matched = arena.span(id) == span
                || self
                    .shared
                    .pools
                    .child_slice(args)
                    .iter()
                    .any(|&arg| arena.span(arg) == span);
            matched.then_some(macro_id)
        }) else {
            return e;
        };
        let config = self.shared.pools.get_macro(macro_id);
        // The defining module is absent from `modules` while it is itself being
        // checked, which is exactly the case where the macro is local.
        let def = self
            .modules
            .get(usize::from(config.def_module()))
            .map_or(current, Module::ctx);
        e.add_note(def.note(NoteMessage::DefinedHere, config.name.span));
        e
    }

    /// Attach a cross-module definition note when a qualified call targets a non-macro export.
    fn note_undefined_macro(&self, current: &ModuleContext, mut e: TypeError) -> TypeError {
        let TypeErrorKind::UndefinedMacro(_) = e.kind else {
            return e;
        };
        let Some(call_span) = e.span else {
            return e;
        };
        let arena = &self.shared.arena;
        let Some(callee) = current.iter_own_nodes(arena).find_map(|(id, node)| {
            if let Node::Call { name, .. } = *node
                && arena.span(id) == call_span
            {
                Some(name)
            } else {
                None
            }
        }) else {
            return e;
        };

        let (ctx, decl) = match *arena.get(callee) {
            Node::Ident(IdentKind::Var(let_id)) => {
                let Some(module) = self.modules.iter().find(|m| m.ctx().owns_node(let_id)) else {
                    return e;
                };
                (module.ctx(), let_id)
            }
            Node::ModuleRule { module, member, .. } => {
                let ctx = self.modules[usize::from(module)].ctx();
                let Some(decl) = ctx.root_items.iter().copied().find(|&id| {
                    let decl_name = match *arena.get(id) {
                        Node::Rule { name, .. } => name,
                        Node::ExpandedRule(expand_id) => {
                            self.shared.pools.get_expansion(expand_id).name
                        }
                        _ => return false,
                    };
                    decl_name == member
                }) else {
                    return e;
                };
                (ctx, decl)
            }
            _ => return e,
        };

        e.add_note(ctx.note(NoteMessage::DefinedHere, arena.span(decl)));
        e
    }

    fn find_cfg_drop<'b>(
        &'b self,
        current: &'b ModuleContext,
        name: StrId,
    ) -> Option<(NodeId, &'b ModuleContext)> {
        if let Some(&id) = current.cfg_dropped.get(&name) {
            return Some((id, current));
        }

        let mut visited = ModuleIdSet::default();
        let mut stack = Vec::new();
        let push_deps = |ctx: &ModuleContext, stack: &mut Vec<ModuleId>| {
            for &ref_id in ctx.module_refs.iter().rev() {
                if let &Node::Import {
                    module: Some(module),
                    ..
                } = self.shared.arena.get(ref_id)
                {
                    stack.push(module);
                }
            }
            if let Some((base, _)) = ctx.inherit_module(&self.shared.arena) {
                stack.push(base);
            }
        };

        // Search only modules whose declarations are visible from the failing module.
        push_deps(current, &mut stack);
        while let Some(module) = stack.pop() {
            if !visited.insert(module) {
                continue;
            }
            let ctx = self.modules[usize::from(module)].ctx();
            if let Some(&id) = ctx.cfg_dropped.get(&name) {
                return Some((id, ctx));
            }
            push_deps(ctx, &mut stack);
        }
        None
    }
}

fn resolve_path(path: &Path, document: DocumentId, span: Span) -> DslResult<PathBuf> {
    dunce::canonicalize(path).map_err(|error| {
        LowerError::new(
            LowerErrorKind::ModuleResolveFailed(IoError {
                error,
                path: Some(path.to_path_buf()),
            }),
            document,
            span,
        )
        .into()
    })
}
