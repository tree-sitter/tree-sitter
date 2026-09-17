//! The core AST [`Node`] enum and the small payload enums it carries.

use super::{ChildRange, ConfigField, ExpandId, ForId, MacroId, NodeId, Span};
use crate::{
    nativedsl::{ModuleId, typecheck::Ty},
    rules::RuleId,
    strpool::StrId,
};

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum PrecKind {
    Default,
    Left,
    Right,
    Dynamic,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum RepeatKind {
    ZeroOrMore,
    OneOrMore,
    Optional,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum BinOp {
    Add,
    Sub,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum IdentKind {
    /// Not yet resolved.
    Unresolved(StrId),
    /// A rule reference.
    Rule(StrId),
    Var(NodeId),
    Macro(MacroId),
}

#[derive(Clone, Copy, Debug)]
pub enum Node {
    Grammar,
    Rule {
        is_override: bool,
        name: StrId,
        body: NodeId,
    },
    /// `rule @<str_expr> { ... }` inside a rule-set macro body.
    /// `name_expr` is `str_t`. The `expand_macro_calls` evaluates
    /// it and emits an `ExpandedRule` node.
    ComputedRule {
        is_override: bool,
        name_expr: NodeId,
        body: NodeId,
    },
    /// Body of a rule-set macro (sequence of `Rule` / `ComputedRule`).
    RuleSet(ChildRange),
    /// One instantiation of a rule-set macro decl at a `@name(args)` call site.
    /// The [`Expansion`](super::Expansion) (side table) carries the computed name, the macro's
    /// id, the *shared template* decl body, and the call's args.
    ExpandedRule(ExpandId),
    /// `let name = value` or `let name: ty = value`. An optional type
    /// annotation lives out-of-line in [`ModuleContext::let_types`](super::ModuleContext) (keyed by
    /// this node's id) so it doesn't widen `Node` past its 16-byte budget.
    Let {
        name: StrId,
        value: NodeId,
    },
    Macro(MacroId),
    /// `expect <name>` top-level forward-declaration: names a symbol defined
    /// elsewhere (a rule, an `externals:` token, or an inherited rule) so this
    /// file can reference it before/without defining it here.
    Forward {
        name: StrId,
    },
    /// A string literal's interned value. Delimiters are excluded and escapes are decoded.
    StringLit(StrId),
    IntLit(i64),
    Ident(IdentKind),
    FieldAccess {
        obj: NodeId,
        field: StrId,
    },
    QualifiedAccess {
        obj: NodeId,
        member: StrId,
        /// Start of the member name token, retained for diagnostics.
        member_offset: u32,
    },
    /// A `mod::name` reference resolved to a rule (or external symbol) in
    /// another module's lowered output. Replaces a `QualifiedAccess` during
    /// resolve once the target is found.
    ModuleRule {
        module: ModuleId,
        member: StrId,
        rule: RuleId,
    },
    /// `seq(a, b, ...)` or `choice(a, b, ...)`. Children: `[member0, member1, ...]`
    SeqOrChoice {
        seq: bool,
        range: ChildRange,
    },
    Repeat {
        kind: RepeatKind,
        inner: NodeId,
    },
    Blank,
    // The `eof()` rule
    Eof,
    Field {
        name: StrId,
        content: NodeId,
    },
    Alias {
        content: NodeId,
        target: NodeId,
    },
    Token {
        immediate: bool,
        inner: NodeId,
    },
    Prec {
        kind: PrecKind,
        value: NodeId,
        content: NodeId,
    },
    Reserved {
        context: StrId,
        content: NodeId,
    },
    /// `concat(a, b, ...)`. Children: `[part0, part1, ...]` - each must be `str_t`.
    Concat(ChildRange),
    /// `regexp(pattern)` or `regexp(pattern, flags)`.
    DynRegex {
        pattern: NodeId,
        flags: Option<NodeId>,
    },
    /// `import("...")`. `module` is `None` after parsing, set to a global index
    /// by the loading pre-pass.
    Import {
        path: Span,
        module: Option<ModuleId>,
    },
    /// `inherit("...")`. `module` is `None` after parsing, set to a global index
    /// by the loading pre-pass.
    Inherit {
        path: Span,
        module: Option<ModuleId>,
    },
    /// `grammar_config(module, field)`: access a specific config field from
    /// an inherited grammar module.
    GrammarConfig {
        module: NodeId,
        field: ConfigField,
    },
    Append {
        left: NodeId,
        right: NodeId,
    },
    /// `for (binding) in <iter> { <body> }`. Expression-context only.
    For {
        for_id: ForId,
        body: NodeId,
    },
    /// `@<str_expr>` inside a rule-set macro body: a reference to a (possibly
    /// computed-name) rule. `expr` is `str_t`.
    SymRef {
        expr: NodeId,
    },
    /// `name(arg0, arg1, ...)`. `args` children: `[arg0, arg1, ...]`.
    Call {
        name: NodeId,
        args: ChildRange,
    },
    /// `[elem0, elem1, ...]`. Children: `[elem0, elem1, ...]`.
    List(ChildRange),
    /// `(elem0, elem1, ...)`. Children: `[elem0, elem1, ...]`.
    Tuple(ChildRange),
    /// `{ key0: val0, key1: val1, ... }`. Fields stored in `SharedAst::object_fields`.
    Object(ChildRange),
    Neg(NodeId),
    /// Integer arithmetic: `lhs + rhs` or `lhs - rhs`. Both operands typecheck
    /// as `int_t`. No multiplication, division, parens, or precedence; the
    /// parser only emits left-associative chains of `+`/`-`.
    BinOp {
        op: BinOp,
        lhs: NodeId,
        rhs: NodeId,
    },
    /// Parameter reference in a macro body. `index` is the position into the
    /// call's arg list; `ty` lets the typechecker avoid a macro-context lookup.
    MacroParam {
        ty: Ty,
        index: u8,
    },
    /// Binding reference in a for-loop body. `for_id` disambiguates the
    /// enclosing frame (for-loops nest); `index` selects within it; `ty`
    /// lets the typechecker avoid a pool lookup.
    ForBinding {
        for_id: ForId,
        ty: Ty,
        index: u8,
    },
    /// `#[cfg(NAME)] ITEM`: gates `child` on the named flag. Survives parse,
    /// and is then dropped (or unwrapped) by the `apply_cfg` pass before resolve.
    Cfg {
        name: StrId,
        /// Start of the flag name token, retained for diagnostics.
        name_offset: u32,
        child: NodeId,
    },
    /// Sentinel value occupying index 0 in the arena. Not part of the public API.
    #[doc(hidden)]
    Unreachable,
}

const _: () = assert!(std::mem::size_of::<Node>() == 16);

impl Node {
    /// Range of children for variadic nodes whose children are a flat list of
    /// `NodeId`s: `SeqOrChoice`, `List`, `Tuple`, `Concat`, and `RuleSet`.
    #[must_use]
    pub const fn child_range(&self) -> Option<ChildRange> {
        match self {
            Self::SeqOrChoice { range: r, .. }
            | Self::List(r)
            | Self::Tuple(r)
            | Self::Concat(r)
            | Self::RuleSet(r) => Some(*r),
            _ => None,
        }
    }

    /// Mutable counterpart to [`Self::child_range`].
    pub const fn child_range_mut(&mut self) -> Option<&mut ChildRange> {
        match self {
            Self::SeqOrChoice { range: r, .. }
            | Self::List(r)
            | Self::Tuple(r)
            | Self::Concat(r)
            | Self::RuleSet(r) => Some(r),
            _ => None,
        }
    }
}
