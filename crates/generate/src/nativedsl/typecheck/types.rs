use serde::{Deserialize, Serialize};

use crate::nativedsl::ModuleId;

/// Top-level type of any DSL expression. Every `Ty` is a value that can be
/// bound to a let, returned from a macro, or passed as an argument.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum Ty {
    Data(DataTy),
    Module(ModuleTy),
}

/// First-class data values.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum DataTy {
    Scalar(ScalarTy),
    /// `tuple_t<a, b>`: a fixed-arity bundle of scalars. A leaf, like `Scalar`.
    Tuple(TupleSig),
    /// `list_t<X>` for leaf `X` (scalar or tuple).
    List(ElemTy),
    /// `list_t<list_t<X>>`. Triple nesting is rejected at parse time.
    ListList(ElemTy),
    /// `obj_t<X>`. The inner type is structurally non-Object, so
    /// `obj_t<obj_t<X>>` is impossible.
    Object(InnerTy),
}

/// Leaf data types.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[repr(u8)]
pub enum ScalarTy {
    Rule = 0,
    Str = 1,
    Int = 2,
}

/// A list element / leaf: a scalar or a tuple of scalars.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum ElemTy {
    Scalar(ScalarTy),
    Tuple(TupleSig),
}

/// Element types allowed inside `obj_t<...>`. Mirrors [`DataTy`] minus the
/// `Object` variant, so `obj_t<obj_t<X>>` is structurally impossible.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum InnerTy {
    Scalar(ScalarTy),
    Tuple(TupleSig),
    List(ElemTy),
    ListList(ElemTy),
}

/// Smallest and largest tuple arity. `(a)`/`()` are not tuples (no grouping
/// operator exists).
pub const TUPLE_MIN_ARITY: usize = 2;
pub const TUPLE_MAX_ARITY: usize = 8;

/// A tuple's element scalar types, made up of eight 2-bit slots, with element
/// `i` in bits `2*i..2*i+2`.
///
/// Each slot holds a [`ScalarTy`] discriminant - `00` rule, `01` str, `10` int,
/// or `11` for an absent slot. Present elements fill a contiguous low prefix,
/// so the arity is the index of the first absent slot.
///
/// ```text
///        slot 7  slot 6  slot 5  slot 4  slot 3  slot 2  slot 1  slot 0
/// bit:   15 14   13 12   11 10    9 8     7 6     5 4     3 2     1 0
///
/// tuple_t<str_t, int_t>  ->  ...all absent...      1 1     1 0     0 1
///                                              absent  int=10  str=01
/// ```
#[derive(Clone, Copy, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct TupleSig(u16);

const TUPLE_SLOT_ABSENT: u16 = 0b11;

/// Why a sequence of element types can't form a tuple signature.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct TupleSigError(pub usize);

impl TupleSig {
    /// Build from element scalars. `Err` if the arity is outside 2..=8.
    pub fn new(elems: &[ScalarTy]) -> Result<Self, TupleSigError> {
        let n = elems.len();
        if !(TUPLE_MIN_ARITY..=TUPLE_MAX_ARITY).contains(&n) {
            return Err(TupleSigError(n));
        }
        // All slots absent, then fill the present prefix.
        let mut bits = u16::MAX;
        for (i, &s) in elems.iter().enumerate() {
            bits &= !(0b11u16 << (2 * i));
            bits |= u16::from(s as u8) << (2 * i);
        }
        Ok(Self(bits))
    }

    #[must_use]
    pub fn arity(self) -> usize {
        (0..TUPLE_MAX_ARITY)
            .position(|i| (self.0 >> (2 * i)) & 0b11 == TUPLE_SLOT_ABSENT)
            .unwrap_or(TUPLE_MAX_ARITY)
    }

    #[must_use]
    pub const fn elem(self, i: usize) -> ScalarTy {
        match (self.0 >> (2 * i)) & 0b11 {
            0 => ScalarTy::Rule,
            1 => ScalarTy::Str,
            _ => ScalarTy::Int,
        }
    }

    pub fn elems(self) -> impl Iterator<Item = ScalarTy> {
        (0..self.arity()).map(move |i| self.elem(i))
    }

    /// Element-wise assignability: same arity and each element widens
    /// (`str_t` -> `rule_t`) to the target's.
    #[must_use]
    pub fn widens_to(self, target: Self) -> bool {
        self.arity() == target.arity()
            && self
                .elems()
                .zip(target.elems())
                .all(|(a, b)| a.widens_to(b))
    }
}

impl std::fmt::Debug for TupleSig {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{self}")
    }
}

impl std::fmt::Display for TupleSig {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str("tuple_t<")?;
        for (i, s) in self.elems().enumerate() {
            if i > 0 {
                f.write_str(", ")?;
            }
            s.fmt(f)?;
        }
        f.write_str(">")
    }
}

impl ScalarTy {
    /// `str_t` widens to `rule_t`; otherwise equality.
    #[must_use]
    const fn widens_to(self, target: Self) -> bool {
        matches!((self, target), (Self::Str, Self::Rule)) || (self as u8 == target as u8)
    }
}

impl ElemTy {
    /// Element-wise assignability for list leaves.
    #[must_use]
    fn widens_to(self, target: Self) -> bool {
        match (self, target) {
            (Self::Scalar(a), Self::Scalar(b)) => a.widens_to(b),
            (Self::Tuple(a), Self::Tuple(b)) => a.widens_to(b),
            _ => false,
        }
    }

    /// The depth-0 [`DataTy`] for this leaf.
    #[must_use]
    const fn to_data(self) -> DataTy {
        match self {
            Self::Scalar(s) => DataTy::Scalar(s),
            Self::Tuple(t) => DataTy::Tuple(t),
        }
    }
}

impl std::fmt::Display for ElemTy {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Scalar(s) => s.fmt(f),
            Self::Tuple(t) => t.fmt(f),
        }
    }
}

/// Module types: results of `import(...)` / `inherit(...)` and the user-facing
/// `library_t` / `grammar_t` annotations.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum ModuleTy {
    /// Result of `import(...)`. Carries the module-list index.
    Library(ModuleId),
    /// Result of `inherit(...)`. Carries the module-list index.
    Grammar(ModuleId),
    /// User-facing `library_t` annotation. Matches any imported library via
    /// [`Ty::is_compatible`].
    AnyLibrary,
    /// User-facing `grammar_t` annotation. Matches any inherited grammar via
    /// [`Ty::is_compatible`].
    AnyGrammar,
}

impl Ty {
    /// Common scalar shorthands. Pattern matching still requires the long
    /// form, but value construction (errors, equality checks, mismatch)
    /// stays terse.
    pub const RULE: Self = Self::Data(DataTy::Scalar(ScalarTy::Rule));
    pub const STR: Self = Self::Data(DataTy::Scalar(ScalarTy::Str));
    pub const INT: Self = Self::Data(DataTy::Scalar(ScalarTy::Int));
    pub const LIST_RULE: Self = Self::Data(DataTy::List(ElemTy::Scalar(ScalarTy::Rule)));
    pub const LIST_LIST_RULE: Self = Self::Data(DataTy::ListList(ElemTy::Scalar(ScalarTy::Rule)));
    pub const OBJ_LIST_RULE: Self = Self::Data(DataTy::Object(InnerTy::List(ElemTy::Scalar(
        ScalarTy::Rule,
    ))));
    pub const ANY_LIBRARY: Self = Self::Module(ModuleTy::AnyLibrary);
    pub const ANY_GRAMMAR: Self = Self::Module(ModuleTy::AnyGrammar);

    /// True for `rule_t` or `str_t` (str widens to rule).
    #[must_use]
    pub const fn is_rule_like(self) -> bool {
        matches!(
            self,
            Self::Data(DataTy::Scalar(ScalarTy::Rule | ScalarTy::Str))
        )
    }

    /// Check if `self` is assignable to `expected`.
    #[must_use]
    pub fn is_compatible(self, expected: Self) -> bool {
        match (self, expected) {
            (Self::Data(a), Self::Data(b)) => a.is_compatible(b),
            (Self::Module(got), Self::Module(want)) => match want {
                ModuleTy::AnyGrammar => {
                    matches!(got, ModuleTy::Grammar(_) | ModuleTy::AnyGrammar)
                }
                ModuleTy::AnyLibrary => {
                    matches!(got, ModuleTy::Library(_) | ModuleTy::AnyLibrary)
                }
                ModuleTy::Library(_) | ModuleTy::Grammar(_) => got == want,
            },
            _ => self == expected,
        }
    }

    /// True if this is any list type. Non-data types are never lists.
    #[must_use]
    pub const fn is_list(self) -> bool {
        matches!(self, Self::Data(d) if d.is_list())
    }

    /// True if this is any object type.
    #[must_use]
    pub const fn is_object(self) -> bool {
        matches!(self, Self::Data(DataTy::Object(_)))
    }

    /// Unwrap an object type to its inner. Returns `None` for non-object types.
    #[must_use]
    pub const fn object_inner(self) -> Option<InnerTy> {
        match self {
            Self::Data(DataTy::Object(i)) => Some(i),
            _ => None,
        }
    }

    /// Widen two types, delegating to [`DataTy::widen`] for data pairs.
    /// Equal non-data types widen to themselves; otherwise `None`.
    #[must_use]
    pub fn widen(self, other: Self) -> Option<Self> {
        match (self, other) {
            (Self::Data(a), Self::Data(b)) => a.widen(b).map(Self::Data),
            _ if self == other => Some(self),
            _ => None,
        }
    }

    /// Promote a data type to its list wrapper. Returns `None` for non-data
    /// or non-list-able types.
    pub fn to_list(self) -> Option<Self> {
        match self {
            Self::Data(d) => d.to_list().map(Self::Data),
            Self::Module(_) => None,
        }
    }

    /// Unwrap a list type to its element type. Returns `None` for non-data
    /// or non-list types.
    pub fn list_elem(self) -> Option<Self> {
        match self {
            Self::Data(d) => d.list_elem().map(Self::Data),
            Self::Module(_) => None,
        }
    }
}

impl DataTy {
    /// True if this is a list type at any depth.
    #[must_use]
    const fn is_list(self) -> bool {
        matches!(self, Self::List(_) | Self::ListList(_))
    }

    /// Check if `self` is assignable to `expected`.
    fn is_compatible(self, expected: Self) -> bool {
        self.widens_to(expected)
            || matches!(
                (self, expected),
                (Self::Object(a), Self::Object(b)) if Self::from(a).widens_to(Self::from(b))
            )
    }

    /// Whether `self` is assignable to `target` via equality or element-wise
    /// `str_t`->`rule_t` widening (at any nesting depth, and per tuple element).
    fn widens_to(self, target: Self) -> bool {
        if self == target {
            return true;
        }
        match (self, target) {
            (Self::Scalar(a), Self::Scalar(b)) => a.widens_to(b),
            (Self::Tuple(a), Self::Tuple(b)) => a.widens_to(b),
            (Self::List(a), Self::List(b)) | (Self::ListList(a), Self::ListList(b)) => {
                a.widens_to(b)
            }
            _ => false,
        }
    }

    /// Widen `self` to accommodate `other`. Returns the wider type, or `None`
    /// if the types are incompatible.
    #[must_use]
    fn widen(self, other: Self) -> Option<Self> {
        if other.is_compatible(self) {
            Some(self)
        } else if self.is_compatible(other) {
            Some(other)
        } else {
            None
        }
    }

    /// Promote to the list wrapper (e.g. `Scalar(Rule)` -> `List(Rule)`).
    /// Returns `None` for types that can't be list elements (objects, or
    /// list-of-list which would be triple-nested).
    const fn to_list(self) -> Option<Self> {
        Some(match self {
            Self::Scalar(s) => Self::List(ElemTy::Scalar(s)),
            Self::Tuple(t) => Self::List(ElemTy::Tuple(t)),
            Self::List(e) => Self::ListList(e),
            Self::ListList(_) | Self::Object(_) => return None,
        })
    }

    /// Unwrap a list type to its element type. Returns `None` for non-list types.
    const fn list_elem(self) -> Option<Self> {
        Some(match self {
            Self::List(e) => e.to_data(),
            Self::ListList(e) => Self::List(e),
            Self::Scalar(_) | Self::Tuple(_) | Self::Object(_) => return None,
        })
    }
}

impl From<InnerTy> for DataTy {
    fn from(i: InnerTy) -> Self {
        match i {
            InnerTy::Scalar(s) => Self::Scalar(s),
            InnerTy::Tuple(t) => Self::Tuple(t),
            InnerTy::List(e) => Self::List(e),
            InnerTy::ListList(e) => Self::ListList(e),
        }
    }
}

impl TryFrom<DataTy> for InnerTy {
    type Error = ();
    fn try_from(d: DataTy) -> Result<Self, ()> {
        Ok(match d {
            DataTy::Scalar(s) => Self::Scalar(s),
            DataTy::Tuple(t) => Self::Tuple(t),
            DataTy::List(e) => Self::List(e),
            DataTy::ListList(e) => Self::ListList(e),
            DataTy::Object(_) => return Err(()),
        })
    }
}

impl From<DataTy> for Ty {
    fn from(d: DataTy) -> Self {
        Self::Data(d)
    }
}

impl From<InnerTy> for Ty {
    fn from(i: InnerTy) -> Self {
        Self::Data(DataTy::from(i))
    }
}

impl std::fmt::Display for Ty {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Data(d) => d.fmt(f),
            Self::Module(ModuleTy::Grammar(_) | ModuleTy::AnyGrammar) => f.write_str("grammar_t"),
            Self::Module(ModuleTy::Library(_) | ModuleTy::AnyLibrary) => f.write_str("library_t"),
        }
    }
}

impl std::fmt::Display for DataTy {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Scalar(s) => s.fmt(f),
            Self::Tuple(t) => t.fmt(f),
            Self::List(e) => write!(f, "list_t<{e}>"),
            Self::ListList(e) => write!(f, "list_t<list_t<{e}>>"),
            Self::Object(i) => write!(f, "obj_t<{i}>"),
        }
    }
}

impl std::fmt::Display for ScalarTy {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(match self {
            Self::Rule => "rule_t",
            Self::Str => "str_t",
            Self::Int => "int_t",
        })
    }
}

impl std::fmt::Display for InnerTy {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        DataTy::from(*self).fmt(f)
    }
}

/// Type expectation propagated to children during type checking.
///
/// Used by `type_of` to give nested empty containers (`[]`, `{}`) enough
/// context to infer their type, and to surface more accurate errors when
/// a value is used in a position with a known shape constraint.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum Constraint {
    /// No constraint, the typed value can be anything bindable.
    None,
    /// Must equal (or widen to) this exact type.
    Exact(Ty),
    /// Must equal this type by strict equality (no widening).
    Strict(Ty),
    /// Must be `Object<?>` for any inner; specific inner is unknown.
    AnyObject,
    /// Must be either `str_t` or `rule_t`.
    RuleLike,
    /// Must be either `int_t` or `str_t`.
    IntOrStr,
}

impl Constraint {
    /// True if `ty` satisfies this constraint via [`Ty::is_compatible`]
    /// (or strict equality, for [`Self::Strict`]).
    #[must_use]
    pub fn satisfies(self, ty: Ty) -> bool {
        match self {
            Self::None => true,
            Self::Exact(t) => ty == t || ty.is_compatible(t),
            Self::Strict(t) => ty == t,
            Self::AnyObject => ty.is_object(),
            Self::RuleLike => ty.is_rule_like(),
            Self::IntOrStr => ty.is_compatible(Ty::INT) || ty.is_compatible(Ty::STR),
        }
    }

    /// Constraint to propagate to a list element. Only `Exact(list_t)`
    /// carries through; other variants degrade to `None`.
    #[must_use]
    pub fn elem(self) -> Self {
        match self {
            Self::Exact(ty) => ty.list_elem().map_or(Self::None, Self::Exact),
            _ => Self::None,
        }
    }

    /// Constraint to propagate to an object value. Only `Exact(obj_t<X>)`
    /// carries through; other variants degrade to `None`.
    #[must_use]
    pub fn object_value(self) -> Self {
        match self {
            Self::Exact(ty) => ty
                .object_inner()
                .map_or(Self::None, |i| Self::Exact(Ty::from(i))),
            _ => Self::None,
        }
    }
}

impl std::fmt::Display for Constraint {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::None => f.write_str("any value"),
            Self::Exact(ty) | Self::Strict(ty) => ty.fmt(f),
            Self::AnyObject => f.write_str("an object"),
            Self::RuleLike => f.write_str("str_t or rule_t"),
            Self::IntOrStr => f.write_str("int_t or str_t"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ScalarTy::{Int, Rule, Str};

    fn sig(elems: &[ScalarTy]) -> TupleSig {
        TupleSig::new(elems).unwrap()
    }

    #[test]
    fn tuple_sig_arity_bounds() {
        assert_eq!(TupleSig::new(&[]), Err(TupleSigError(0)));
        assert_eq!(TupleSig::new(&[Rule]), Err(TupleSigError(1)));
        // One past the max (9 elements) is rejected with its actual count.
        assert_eq!(TupleSig::new(&[Rule; 9]), Err(TupleSigError(9)));
        for n in TUPLE_MIN_ARITY..=TUPLE_MAX_ARITY {
            let elems = vec![Rule; n];
            assert_eq!(sig(&elems).arity(), n);
        }
    }

    #[test]
    fn tuple_sig_roundtrips_elements() {
        // Exhaustively pack/unpack every scalar combination at every arity,
        // enumerating the 3^n combos as base-3 digits over [Rule, Str, Int].
        let all = [Rule, Str, Int];
        for n in TUPLE_MIN_ARITY..=TUPLE_MAX_ARITY {
            for combo in 0..3usize.pow(n as u32) {
                let elems: Vec<ScalarTy> = (0..n)
                    .map(|i| all[combo / 3usize.pow(i as u32) % 3])
                    .collect();
                let s = sig(&elems);
                assert_eq!(s.arity(), n);
                assert_eq!(s.elems().collect::<Vec<_>>(), elems);
            }
        }
    }

    #[test]
    fn tuple_sig_widening_is_elementwise() {
        // str -> rule per element; arity must match.
        assert!(sig(&[Str, Int]).widens_to(sig(&[Rule, Int])));
        assert!(sig(&[Str, Str]).widens_to(sig(&[Rule, Rule])));
        assert!(sig(&[Rule, Int]).widens_to(sig(&[Rule, Int]))); // exact
        // rule does NOT widen to str; int does not widen.
        assert!(!sig(&[Rule, Int]).widens_to(sig(&[Str, Int])));
        assert!(!sig(&[Int, Int]).widens_to(sig(&[Rule, Int])));
        // arity mismatch never widens.
        assert!(!sig(&[Str, Str]).widens_to(sig(&[Rule, Rule, Rule])));
    }

    #[test]
    fn tuple_nests_in_lists_to_depth_two() {
        let t = sig(&[Rule, Int]);
        let tuple = DataTy::Tuple(t);
        let list = tuple.to_list().unwrap();
        assert_eq!(list, DataTy::List(ElemTy::Tuple(t)));
        let list_list = list.to_list().unwrap();
        assert_eq!(list_list, DataTy::ListList(ElemTy::Tuple(t)));
        // depth 3 is rejected.
        assert_eq!(list_list.to_list(), None);
        // list_elem is the inverse.
        assert_eq!(list_list.list_elem(), Some(list));
        assert_eq!(list.list_elem(), Some(tuple));
        assert_eq!(tuple.list_elem(), None);
    }

    #[test]
    fn list_of_tuples_widens_elementwise() {
        let strs = DataTy::List(ElemTy::Tuple(sig(&[Str, Int])));
        let rules = DataTy::List(ElemTy::Tuple(sig(&[Rule, Int])));
        assert!(strs.widens_to(rules));
        assert!(!rules.widens_to(strs));
        assert_eq!(strs.widen(rules), Some(rules));
    }

    #[test]
    fn objects_hold_tuples_and_invariant_holds() {
        // InnerTy == DataTy minus Object: tuple round-trips, object is rejected.
        let t = DataTy::Tuple(sig(&[Rule, Str]));
        let inner = InnerTy::try_from(t).unwrap();
        assert_eq!(DataTy::from(inner), t);
        let tl = DataTy::List(ElemTy::Tuple(sig(&[Rule, Str])));
        assert!(InnerTy::try_from(tl).is_ok());
        assert!(InnerTy::try_from(DataTy::Object(InnerTy::Scalar(Rule))).is_err());
    }
}
