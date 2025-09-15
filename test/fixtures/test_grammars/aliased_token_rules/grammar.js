// This grammar shows that `ALIAS` rules can be applied directly to `TOKEN` and `IMMEDIATE_TOKEN`
// rules.

export default grammar({
    name: 'aliased_token_rules',

    extras: $ => [/\s/],

    rules: {
        expression: $ => seq(
            'a',
            alias(token(seq('b', 'c')), $.X),
            alias(token.immediate(seq('d', 'e')), $.Y),
        ),
    }
});