TODO
====

# complete the list of rule types

- add repeat rules
- parse regex rules into trees of choices, sequences, repeats

# generate lexers for sets of terminal rules (can be mix of throwaway and meaningful)

Introduce ParseTable type which contains a vector of ParseStates. A ParseState contains a
TransitionMap of ParseActions. For a lexer, a ParseAction can be one of:
    - Accept(symbol)
    - Advance(state index)

Then generate a C function for a ParseTable

# generate parsers from sets of non-termina rules

For a Parser, the ParseActions can be any of:
    - Accept(symbol)
    - Shift(state_index)
    - Reduce(symbol, number of child symbols)
    
# normalize grammars

- add concept of throwaway-terminals (tokens that won't appear in constructed AST)
- classify rules as non-terminals or terminals
- extract strings and regexes from non-terminal rules into their own throwaway-terminals,
    in order to separate lexing from parsing

After this, a grammar will have these fields:
- non-terminal rules
- terminal rules
- throwaway terminal rules

