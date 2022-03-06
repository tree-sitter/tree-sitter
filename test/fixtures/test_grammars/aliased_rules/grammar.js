module.exports = grammar({
    name: 'aliased_rules',

    extras: $ => [/\s/],

    rules: {
        statement: $ => seq($._expression, ';'),

        _expression: $ => choice(
            $.call_expression,
            $.member_expression,
            alias($.identifier, $.variable_name),
        ),

        call_expression: $ => prec.left(seq(
            $._expression,
            '(',
            $._expression,
            ')'
        )),

        member_expression: $ => prec.left(1, seq(
            $._expression,
            '.',
            alias($.identifier, $.property_name)
        )),

        identifier: $ => /[a-z]+/
    }
});