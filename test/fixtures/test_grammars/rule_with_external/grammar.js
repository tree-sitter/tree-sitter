// Copy of external_and_internal_tokens
// @ts-check
/// <reference path="../../../../cli/npm/dsl.d.ts" />

module.exports = grammar({
    name: 'rule_with_external',

    externals: $ => [
        $.string,
        $.line_break,
    ],

    extras: $ => [/\s/],

    rules: {
        string: EXTERNAL,

        statement: $ => seq(
            $._expression,
            $._expression,
            $.line_break,
        ),

        _expression: $ => choice(
            $.string,
            $.variable,
            $.number,
        ),

        variable: $ => /[a-z]+/,
        number: $ => /\d+/,
        line_break: $ => '\n',
    }
});