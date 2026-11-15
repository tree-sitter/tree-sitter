// A `declaration` ends with a zero-width token: an automatic semicolon from the external scanner
// (at a newline right after the previous token), or the lexer's `_semicolon`, which is a `;` or
// nothing. When the next line starts with a tab, the scanner adds a second zero-width token after
// the automatic semicolon, `_empty`, and the `declaration` ends with that one. After `for (let j`,
// the first zero-width token splits the stack between a `for_declaration` and a `for_of`, and only
// the token after the zero-width ones settles the split. A zero-width token doesn't move the parser
// forward, so the stack can be condensed before the `declaration` is reduced, by the one version
// left. Deleting `of` makes the `for_declaration` win; the reparse after putting `of` back must not
// reuse that `declaration`.

export default grammar({
    name: 'reuse_zero_width_last_leaf',

    word: $ => $.identifier,
    externals: $ => [$._automatic_semicolon, $._empty],
    conflicts: $ => [[$.declarator, $.for_of]],

    rules: {
        source_file: $ => repeat($._statement),
        _statement: $ => choice($.for_declaration, $.for_of),
        for_declaration: $ => seq('for', '(', $.declaration, $.identifier, ')'),
        declaration: $ => seq('let', $.declarator, $._terminator, optional($._empty)),
        declarator: $ => $.identifier,
        for_of: $ => seq(
            'for', '(', 'let', $.identifier, optional($._terminator), 'of', $.identifier, ')',
        ),
        _terminator: $ => choice($._automatic_semicolon, $._semicolon),
        _semicolon: _ => token(/;?/),
        identifier: _ => /[a-z]+/,
    },
});
