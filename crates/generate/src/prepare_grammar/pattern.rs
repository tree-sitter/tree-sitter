//! Parsing of token patterns.
//!
//! Unicode simple case folding maps two non-ASCII code points onto ASCII letters:
//!     - the long s `ſ` onto `s`
//!     - the Kelvin sign `K` onto `k`
//!
//! Taken as is, every case-insensitive ASCII token picks both up, which is virtually
//! never intended and stops the token from being extracted as a keyword. To
//! fix this, we expand the `i` flag ourselves.
//!
//! The [`regex_syntax`] crate parses a pattern into an [`ast::Ast`], then lowers
//! it to an [`hir::Hir`] via a [`hir::translate::Translator`]. The translator is
//! what applies `i`, and it folds each leaf of a class expression before applying
//! that leaf's negation and the set algebra above it. This order is what makes
//! `(?i)[^x]` exclude `X` rather than re-admit it, so we keep that order and only
//! change the fold:
//!     - Walk the AST
//!     - Fold each leaf as if `ſ` and `K` were their own equivalence classes
//!     - Hand the result to the translator with its own folding turned off
//!
//! Folding at the leaves is sufficient for correctness, as case folding sorts every
//! character into a group of case variants (`{a, A}`, `{s, S, ſ}`, etc.), with
//! each character in exactly one group. Folding a set adds (for each character
//! in it) the rest of that character's group, so the result is always built out
//! of whole groups. Negation and set algebra preserve that, because they treat
//! every character in a group alike: a group ends up either wholly inside or wholly
//! outside the result. Folding a set that is already whole groups adds nothing,
//! so once leaves are folded, every fold the translator would still apply does
//! nothing and it compiles exactly what is would have with our fold in place of
//! its own.

use regex_syntax::{
    ast::{
        self, Ast, ClassBracketed, ClassSet, ClassSetItem, ClassSetRange, ClassSetUnion, Flag,
        FlagsItem, FlagsItemKind, GroupKind, Span, parse::ParserBuilder,
    },
    hir::{
        self, Class, ClassUnicode, ClassUnicodeRange, Hir, HirKind,
        translate::{Translator, TranslatorBuilder},
    },
};

/// The flags that decide whether we fold a scope's leaves.
#[derive(Clone, Copy)]
struct FoldMode {
    case_insensitive: bool,
    unicode: bool,
}

impl FoldMode {
    /// Whether we fold this scope's leaves ourselves.
    ///
    /// Inside `(?-u:...)` the translator works on bytes and folds ASCII only, which
    /// can never pull in `ſ` or `K`, so those scopes keep its folding.
    const fn folds_here(self) -> bool {
        self.case_insensitive && self.unicode
    }
}

/// The state of the walk: The flags in effect, and one translator to resolve
/// `\p{...}` and friends without rebuilding it per leaf.
struct Expander<'a> {
    translator: Translator,
    pattern: &'a str,
    mode: FoldMode,
}

/// Parse a token pattern into an [`Hir`], folding any `i` flag manually.
pub(super) fn parse(
    pattern: &str,
    case_insensitive: bool,
) -> Result<Hir, Box<regex_syntax::Error>> {
    let mut ast = ParserBuilder::new()
        .build()
        .parse(pattern)
        .map_err(|e| Box::new(e.into()))?;

    let mut expander = Expander {
        translator: TranslatorBuilder::new()
            .case_insensitive(false)
            .unicode(true)
            .utf8(false)
            .build(),
        pattern,
        mode: FoldMode {
            case_insensitive,
            unicode: true,
        },
    };
    expander.expand(&mut ast).map_err(|e| Box::new(e.into()))?;
    expander
        .translator
        .translate(pattern, &ast)
        .map_err(|e| Box::new(e.into()))
}

impl Expander<'_> {
    fn expand(&mut self, ast: &mut Ast) -> Result<(), hir::Error> {
        match ast {
            Ast::Flags(f) => self.set_flags(&mut f.flags),
            Ast::Repetition(r) => self.expand(&mut r.ast)?,
            Ast::Group(g) => {
                let outer = self.mode;
                if let GroupKind::NonCapturing(flags) = &mut g.kind {
                    self.set_flags(flags);
                }
                self.expand(&mut g.ast)?;
                self.mode = outer;
            }
            // Flags set in one branch carry into the next, as they do in the translator,
            // which scopes flags to groups but not to these.
            Ast::Alternation(a) => {
                for branch in &mut a.asts {
                    self.expand(branch)?;
                }
            }
            Ast::Concat(c) => {
                for element in &mut c.asts {
                    self.expand(element)?;
                }
            }
            Ast::ClassBracketed(b) if self.mode.folds_here() => {
                self.expand_class_set(&mut b.kind)?;
            }
            // The remaining class-valued nodes are the same leaves as a bracket holds,
            // so they fold through the same path.
            _ if self.mode.folds_here() => {
                let mut item = match ast {
                    Ast::Literal(l) => ClassSetItem::Literal((**l).clone()),
                    Ast::ClassUnicode(u) => ClassSetItem::Unicode((**u).clone()),
                    Ast::ClassPerl(p) => ClassSetItem::Perl((**p).clone()),
                    // `.` is fold-closed, nothing else matches a character
                    _ => return Ok(()),
                };
                self.expand_class_item(&mut item)?;
                if let ClassSetItem::Bracketed(class) = item {
                    *ast = Ast::ClassBracketed(class);
                }
            }
            // Left to the translator: either no `i` is in effect, or this is a
            // `(?-u:...)` scope, where its own folding is ASCII-only and cannot
            // pull in `ſ` or `K`.
            #[rustfmt::skip]
            Ast::Empty(_) | Ast::Dot(_) | Ast::Assertion(_) | Ast::Literal(_)
            | Ast::ClassUnicode(_) | Ast::ClassPerl(_) | Ast::ClassBracketed(_) => {}
        }
        Ok(())
    }

    /// Apply a flag directive to the mode, then rewrite the directive to say what
    /// the translator should still do about `i` in the scope it opens.
    ///
    /// `i` comes out everywhere, since folding a leaf we already folded would put
    /// `ſ`/`K` back in, and goes back in only when we skipped the folding outselves
    /// (inside `(?-u:...)`.
    ///
    /// `i` comes out everywhere, since folding a leaf we already folded would put
    /// `ſ`/`K` straight back. It goes back in wherever [`FoldMode::folds_here`]
    /// says we left the folding alone, which would otherwise lose case-insensitivity
    /// in that scope entirely.
    fn set_flags(&mut self, flags: &mut ast::Flags) {
        let mut negated = false;
        for item in &flags.items {
            match item.kind {
                FlagsItemKind::Negation => negated = true,
                FlagsItemKind::Flag(Flag::CaseInsensitive) => self.mode.case_insensitive = !negated,
                FlagsItemKind::Flag(Flag::Unicode) => self.mode.unicode = !negated,
                FlagsItemKind::Flag(_) => {}
            }
        }
        let item = |kind| FlagsItem {
            span: flags.span,
            kind,
        };
        flags
            .items
            .retain(|it| !matches!(it.kind, FlagsItemKind::Flag(Flag::CaseInsensitive)));
        if self.mode.folds_here() {
            flags.items.push(item(FlagsItemKind::Negation));
            flags
                .items
                .push(item(FlagsItemKind::Flag(Flag::CaseInsensitive)));
        } else if self.mode.case_insensitive {
            flags
                .items
                .insert(0, item(FlagsItemKind::Flag(Flag::CaseInsensitive)));
        }
    }

    /// Fold the leaves of a class expression, leaving its structure alone. The
    /// translator still performs the negations and the `&&`/`--`/`~~` itself, on
    /// operands that are already folded.
    fn expand_class_set(&mut self, set: &mut ClassSet) -> Result<(), hir::Error> {
        match set {
            ClassSet::Item(item) => self.expand_class_item(item),
            ClassSet::BinaryOp(op) => {
                self.expand_class_set(&mut op.lhs)?;
                self.expand_class_set(&mut op.rhs)
            }
        }
    }

    fn expand_class_item(&mut self, item: &mut ClassSetItem) -> Result<(), hir::Error> {
        // Whether the leaf carries its own negation (`\P{L}, `[:^alpha:]`, `\D`, etc.).
        let (span, negated) = match item {
            ClassSetItem::Bracketed(b) => return self.expand_class_set(&mut b.kind),
            ClassSetItem::Union(u) => {
                return u
                    .items
                    .iter_mut()
                    .try_for_each(|i| self.expand_class_item(i));
            }
            ClassSetItem::Empty(_) => return Ok(()),
            ClassSetItem::Literal(l) => (l.span, false),
            ClassSetItem::Range(r) => (r.span, false),
            ClassSetItem::Ascii(a) => (a.span, a.negated),
            ClassSetItem::Perl(p) => (p.span, p.negated),
            ClassSetItem::Unicode(u) => (u.span, u.is_negated()),
        };

        // `leaf_set` applies the leaf's own negation, so undo it to recover the
        // operand the translator would have folded, and hand the negation back
        // to the replacement so it is reapplied after the fold.
        let mut operand = self.leaf_set(item)?;
        if negated {
            operand.negate();
        }

        let mut folded = operand.clone();
        Self::fold_ascii_safe(&mut folded);
        // A leaf that is already fold-closed stays as written, which keeps most
        // unicode properties out of the expansion.
        if folded.ranges() != operand.ranges() {
            *item = ClassSetItem::Bracketed(Box::new(ClassBracketed {
                span,
                negated,
                kind: ClassSet::Item(Self::class_to_item(span, &folded)),
            }));
        }

        Ok(())
    }

    /// The set a leaf denotes, with any negation of its own already applied.
    ///
    /// Literals and ranges are read directly from the AST. Everything else goes
    /// back through the translator, which own the property and POSIX tables.
    fn leaf_set(&mut self, item: &ClassSetItem) -> Result<ClassUnicode, hir::Error> {
        let range = match item {
            ClassSetItem::Literal(l) => ClassUnicodeRange::new(l.c, l.c),
            ClassSetItem::Range(r) => ClassUnicodeRange::new(r.start.c, r.end.c),
            _ => {
                let ast = Ast::ClassBracketed(Box::new(ClassBracketed {
                    span: *item.span(),
                    negated: false,
                    kind: ClassSet::Item(item.clone()),
                }));
                return Ok(Self::class_of(
                    self.translator.translate(self.pattern, &ast)?,
                ));
            }
        };
        Ok(ClassUnicode::new([range]))
    }

    /// The class a single-class [`Hir`] denotes.
    ///
    /// We only ever translate one [`Ast::ClassBracketed`], so [`Hir::class`] built
    /// the result: A class, or one of the two shapes it collapses to. The structural
    /// kinds (`Empty`, `Look`, `Repetition`, `Capture`, `Concat`, `Alternation`)
    /// need AST nodes we never construct in [`Self::leaf_set`].
    fn class_of(hir: Hir) -> ClassUnicode {
        match hir.into_kind() {
            HirKind::Class(Class::Unicode(class)) => class,
            HirKind::Literal(literal) => {
                // A one character class, translated in unicode mode, so this must
                // be that character's UTF-8.
                let literal = str::from_utf8(&literal.0).unwrap();
                ClassUnicode::new(literal.chars().map(|c| ClassUnicodeRange::new(c, c)))
            }
            // An empty class collapses to `Hir::fail` (an empty byte class).
            _ => ClassUnicode::empty(),
        }
    }

    /// Re-encode a class of the AST nodes the tranlator will read back, the inverse
    /// of [`Self::leaf_set`].
    ///
    /// Every node reuses the leaf's own span to preserve error spans. The literal
    /// kind is irrelevant, in unicode mode the translator only reads `c`.
    fn class_to_item(span: Span, class: &ClassUnicode) -> ClassSetItem {
        let literal = |c| ast::Literal {
            span,
            kind: ast::LiteralKind::Verbatim,
            c,
        };
        ClassSetUnion {
            span,
            items: class
                .ranges()
                .iter()
                .map(|r| {
                    ClassSetItem::Range(ClassSetRange {
                        span,
                        start: literal(r.start()),
                        end: literal(r.end()),
                    })
                })
                .collect(),
        }
        .into_item()
    }

    /// Fold `class` in place, with `ſ` and `K` each in a group of their own rather
    /// than the the `s`/`S` and `k`/`K` groups.
    ///
    /// Dropping them before the fold stops a `ſ` in the class from pulling in `s`/`S`.
    /// Dropping them after removes the ones folding `s`/`S` introduced. The union
    /// restores any the class genuinely held.
    fn fold_ascii_safe(class: &mut ClassUnicode) {
        // The code points that Unicode simple case folding maps onto ASCII letters:
        // the long s `ſ` folds with `s`/`S`, and the Kelvin sign `K` with `k`/`K`.
        const NON_ASCII_FOLDS: [char; 2] = ['\u{17f}', '\u{212a}'];
        let exotic = ClassUnicode::new(NON_ASCII_FOLDS.map(|c| ClassUnicodeRange::new(c, c)));

        // The ones the pattern asked for itself, which folding  must not drop
        let mut asked_for = exotic.clone();
        asked_for.intersect(class);

        class.difference(&exotic);
        class.case_fold_simple();
        class.difference(&exotic);
        class.union(&asked_for);
    }
}
