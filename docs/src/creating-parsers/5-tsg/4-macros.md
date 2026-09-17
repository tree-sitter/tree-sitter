# Macros

TSG has two kinds of macros, both expanded at compile time. Expansion is hygienic and operates on the AST rather than
text. Arguments are typed values rather than token pastes, and names inside a macro body resolve where the macro is
defined, not where it is called. Both kinds are callable from other modules with `lib::name`.

## Expression macros

- **`macro name(param: type_t, ...) return_t { expression }`** defines a macro used like a builtin call. Each call is
checked and expanded with its own arguments.

```tsg
macro sep1(item: rule_t, s: str_t) rule_t {
    seq(item, repeat(seq(s, item)))
}

rule arguments { sep1(identifier, ",") }
```

## Rule-set macros

- **`rules name(param: type_t, ...) { ... }`** defines a macro whose body contains only `rule` declarations, including
`override rule`. Invoking `@name(args)` at the top level stamps those rules into the grammar, and a family of rules
comes from invoking the macro once per member.
- A rule name inside the body can be computed with `@`. `rule @concat(name, "_open") { ... }` names the rule from a
parameter, and `@concat(...)` in expression position references a rule named the same way.
- Generated names evaluate before the rest of the grammar resolves, so they can use parameters, literals, and `concat`
of those, but not `let` bindings. Pass the value in as a parameter instead.

## A worked example

```tsg
rules token_pair(name: str_t, open: str_t, close: str_t) {
    rule @concat(name, "_open") { open }
    rule @concat(name, "_close") { close }
    rule @concat(name, "_block") {
        seq(@concat(name, "_open"), repeat(word), @concat(name, "_close"))
    }
}

grammar { language: "example", start: program, extras: [regexp(r"\s")] }

@token_pair("paren", "(", ")")
@token_pair("brace", "{", "}")

rule program { repeat(choice(paren_block, brace_block)) }
rule word { regexp("[a-z]+") }
```

The two invocations define `paren_open`, `paren_close`, `paren_block`, `brace_open`, `brace_close`, and `brace_block`,
alongside the handwritten `program` and `word`.
