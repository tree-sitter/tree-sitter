//! Per-module parser output: [`ModuleContext`], the grammar block
//! ([`GrammarConfig`]/[`ConfigField`]), and their accessors.

use rustc_hash::FxHashMap;

use super::{Node, NodeArena, NodeId, Span};
use crate::{
    nativedsl::{DocumentId, DocumentSpan, ModuleId, Note, NoteMessage, typecheck::Ty},
    strpool::StrId,
};

macro_rules! define_grammar_config {
    (
        values {
            $(
                $value_field:ident: $value_ty:ty =
                    $value_variant:ident($value_name:literal)
            ),* $(,)?
        }
        nodes {
            $(
                $node_field:ident = $node_variant:ident($node_name:literal)
            ),* $(,)?
        }
    ) => {
        /// Identifies a field in the grammar configuration block.
        #[derive(Clone, Copy, Debug)]
        pub enum ConfigField {
            $($value_variant,)*
            $($node_variant,)*
        }

        impl ConfigField {
            pub const COUNT: usize = [
                $(Self::$value_variant,)*
                $(Self::$node_variant,)*
            ]
            .len();
        }

        impl TryFrom<&str> for ConfigField {
            type Error = ();
            fn try_from(value: &str) -> Result<Self, Self::Error> {
                Ok(match value {
                    $($value_name => Self::$value_variant,)*
                    $($node_name => Self::$node_variant,)*
                    _ => return Err(()),
                })
            }
        }

        #[derive(Clone, Default, Debug)]
        pub struct GrammarConfig {
            $(pub $value_field: Option<$value_ty>,)*
            $(pub $node_field: Option<NodeId>,)*
        }

        impl GrammarConfig {
            /// All node-valued config fields with their `ConfigField` kind.
            pub fn node_fields(&self) -> impl Iterator<Item = (ConfigField, NodeId)> + '_ {
                let fields = [
                    $((ConfigField::$node_variant, self.$node_field),)*
                ];
                fields
                    .into_iter()
                    .filter_map(|(field, id)| id.map(|id| (field, id)))
            }
        }
    };
}

define_grammar_config! {
    values {
        language: StrId = Language("language"),
    }
    nodes {
        inherits = Inherits("inherits"),
        extras = Extras("extras"),
        externals = Externals("externals"),
        supertypes = Supertypes("supertypes"),
        inline = Inline("inline"),
        word = Word("word"),
        conflicts = Conflicts("conflicts"),
        precedences = Precedences("precedences"),
        reserved = Reserved("reserved"),
        start = Start("start"),
        flags = Flags("flags"),
    }
}

/// Per-module state produced by the parser. Its nodes live in the
/// [`SharedAst`](super::SharedAst) shared by the entire grammar.
#[derive(Debug)]
pub struct ModuleContext {
    pub document: DocumentId,
    pub grammar_config: Option<GrammarConfig>,
    pub root_items: Vec<NodeId>,
    /// All `Import` and `Inherit` nodes in source order, collected by the parser.
    pub module_refs: Vec<NodeId>,
    /// `true` if the parser pushed at least one `Node::Cfg` for this module.
    pub has_cfg: bool,
    /// `true` if the parser pushed at least one `Node::Forward` for this module.
    pub has_forward_decls: bool,
    /// Flag names declared in this module's `flags`, mapped to the span of
    /// their first occurrence (used for `FirstDefinedHere` notes).
    pub cfg_declared: FxHashMap<StrId, Span>,
    /// Top-level declarations dropped by cfg in this module: name -> Cfg
    /// node id. Drives `GatedByDisabledCfg` enrichment.
    pub cfg_dropped: FxHashMap<StrId, NodeId>,
    /// Computed-name references (`@<expr>`) from rule-set macro instances,
    /// evaluated under each call's args at expand time. The macro's defining
    /// module is included alongside.
    pub computed_refs: Vec<(StrId, DocumentSpan)>,
    /// Optional `let name: ty` annotations, keyed by the `Node::Let` id. Stored
    pub let_types: FxHashMap<NodeId, Ty>,
    /// Half-open range of nodes this module owns in the shared arena.
    node_range: std::ops::Range<NodeId>,
    /// A second owned range for nodes created after child modules have loaded.
    late_node_range: Option<std::ops::Range<NodeId>>,
}

impl ModuleContext {
    pub(crate) fn new(document: DocumentId, root_capacity: usize, node_start: NodeId) -> Self {
        Self {
            document,
            grammar_config: None,
            root_items: Vec::with_capacity(root_capacity),
            module_refs: Vec::new(),
            has_cfg: false,
            has_forward_decls: false,
            cfg_declared: FxHashMap::default(),
            cfg_dropped: FxHashMap::default(),
            computed_refs: Vec::new(),
            let_types: FxHashMap::default(),
            node_range: node_start..node_start,
            late_node_range: None,
        }
    }

    /// The [`Node::Inherit`] nodes in source order, derived from `module_refs`. The first
    /// is the active base, a second means `MultipleInherits` (reported by `validate_grammar`).
    pub fn inherits<'a>(&'a self, arena: &'a NodeArena) -> impl Iterator<Item = NodeId> + 'a {
        self.module_refs
            .iter()
            .copied()
            .filter(|&r| matches!(arena.get(r), Node::Inherit { .. }))
    }

    /// The resolved inherited-module index and its `inherit(...)` call span,
    /// once the loader has populated it. `None` before child loading completes.
    #[must_use]
    pub fn inherit_module(&self, arena: &NodeArena) -> Option<(ModuleId, Span)> {
        let id = self.inherits(arena).next()?;
        let &Node::Inherit {
            module: Some(idx), ..
        } = arena.get(id)
        else {
            return None;
        };
        Some((idx, arena.span(id)))
    }

    /// Iterate this module's own [`Node`]s in allocation order.
    ///
    /// `arena` must be the shared arena backing this context.
    ///
    /// # Panics
    ///
    /// The returned iterator panics if the recorded range exceeds `arena`.
    pub fn iter_own_nodes<'a>(
        &self,
        arena: &'a NodeArena,
    ) -> impl Iterator<Item = (NodeId, &'a Node)> {
        arena
            .iter_range(self.node_range.clone())
            .chain(self.late_nodes(arena))
    }

    /// Iterate the nodes this module allocated after its children loaded.
    ///
    /// `arena` must be the shared arena backing this context.
    pub(crate) fn late_nodes<'a>(
        &self,
        arena: &'a NodeArena,
    ) -> impl Iterator<Item = (NodeId, &'a Node)> {
        self.late_node_range
            .clone()
            .into_iter()
            .flat_map(|range| arena.iter_range(range))
    }

    /// Whether `id` lies in one of this module's owned arena ranges.
    #[must_use]
    pub fn owns_node(&self, id: NodeId) -> bool {
        let contains = |r: &std::ops::Range<NodeId>| {
            r.start.index() <= id.index() && id.index() < r.end.index()
        };
        contains(&self.node_range) || self.late_node_range.as_ref().is_some_and(contains)
    }

    pub(crate) fn set_node_end(&mut self, end: NodeId) {
        debug_assert!(end.index() >= self.node_range.end.index());
        self.node_range.end = end;
    }

    pub(crate) fn start_late_nodes(&mut self, start: NodeId) {
        debug_assert!(start.index() >= self.node_range.end.index());
        debug_assert!(self.late_node_range.is_none());
        self.late_node_range = Some(start..start);
    }

    pub(crate) fn set_late_node_end(&mut self, end: NodeId) {
        let range = self.late_node_range.as_mut().unwrap();
        debug_assert!(end.index() >= range.end.index());
        range.end = end;
    }

    /// Build a [`Note`] anchored to this module's source.
    #[must_use]
    pub const fn note(&self, message: NoteMessage, span: Span) -> Note {
        Note {
            message,
            location: DocumentSpan::new(self.document, span),
        }
    }
}
