//! Type-check-stage error taxonomy.

use serde::{Deserialize, Serialize};
use thiserror::Error;

use super::ContainerKind;
use super::types::{self, Constraint, Ty};
use crate::nativedsl::TypeError;

pub type TypeResult<T> = Result<T, TypeError>;

#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum TypeErrorKind {
    #[error("expected {expected}, got {got}")]
    TypeMismatch { expected: Ty, got: Ty },
    #[error("expected {expected}, got {got}")]
    ConstraintMismatch { expected: Constraint, got: Ty },
    #[error("undefined macro '{0}'")]
    UndefinedMacro(String),
    #[error("macro '{macro_name}': expected {expected} arguments, got {got}")]
    ArgCountMismatch {
        macro_name: String,
        expected: usize,
        got: usize,
    },
    #[error("object has no field '{field}'; available: {}", available.join(", "))]
    FieldNotFound {
        field: String,
        available: Vec<String>,
    },
    #[error("list elements have inconsistent types: {first} vs {got}")]
    ListElementTypeMismatch { first: Ty, got: Ty },
    #[error("object field values have inconsistent types: {first} vs {got}")]
    ObjectFieldTypeMismatch { first: Ty, got: Ty },
    #[error("object values cannot be modules or nested objects, got {0}")]
    InvalidObjectValue(Ty),
    #[error(
        "list elements cannot be {0}. Lists allow rule_t, str_t, int_t, tuples, or one nested list"
    )]
    InvalidListElement(Ty),
    #[error("empty {0} requires a type annotation")]
    EmptyContainerNeedsAnnotation(ContainerKind),
    #[error("annotation {declared} is not a {kind} type, but value is an empty {kind} literal")]
    EmptyContainerAnnotationMismatch { declared: Ty, kind: ContainerKind },
    #[error("for-expression requires a list, got {0}")]
    ForRequiresList(Ty),
    #[error("for with multiple bindings requires a list of tuples")]
    ForRequiresTuples,
    #[error("for has {bindings} bindings but tuples have {tuple_elements} elements")]
    ForBindingCountMismatch {
        bindings: usize,
        tuple_elements: usize,
    },
    #[error("append requires list arguments, got {0}")]
    AppendRequiresList(Ty),
    #[error("alias target must be a name or string, got {0}")]
    InvalidAliasTarget(Ty),
    #[error("expected a rule name")]
    ExpectedRuleName,
    #[error("grammar_config() requires an inherited grammar, not an imported module")]
    GrammarConfigRequiresInherit,
    #[error("'inherits' must resolve to this grammar's inherit() call")]
    InheritsMustReferenceBase,
    #[error(
        "tuples must have {min} to {max} elements (there is no grouping operator, so `(x)` is not a value); got {0}",
        min = types::TUPLE_MIN_ARITY,
        max = types::TUPLE_MAX_ARITY
    )]
    TupleArityInvalid(usize),
    #[error("tuple elements must be rule_t, str_t, or int_t, got {0}")]
    TupleElementNotScalar(Ty),
    #[error(
        "a for-loop cannot be used here; for-loops are expanded inline and may only appear inside a sequence, choice, or list"
    )]
    BoundForLoop,
    #[error("imported module has no macro '{0}'")]
    ImportMacroNotFound(String),
    #[error("member access with `::` requires a module bound by import() or inherit(), got {0}")]
    MemberAccessRequiresModule(Ty),
    #[error("a module type cannot be a macro parameter or return type")]
    ModuleTypeNotAllowed,
    #[error("duplicate parameter name '{0}'")]
    DuplicateParameter(String),
    #[error("duplicate binding name '{0}'")]
    DuplicateBinding(String),
    #[error("duplicate object key '{0}'")]
    DuplicateObjectKey(String),
    #[error("for-loop requires at least one binding")]
    EmptyForBindings,
    #[error("'{0}' is a macro, not a value; call it with {0}(...)")]
    MacroUsedAsValue(String),
    #[error("rule-set macro '{0}' can only be invoked at top level, not in expression context")]
    RuleSetMacroInExpressionContext(String),
    #[error(
        "reserved must be an object literal `{{ name: [...] }}`; its first set is the default \
         applied to every token, so the set order must be explicit (not a computed value)"
    )]
    ReservedMustBeLiteral,
    #[error("let '{0}' is defined in terms of itself")]
    CircularLet(String),
}
