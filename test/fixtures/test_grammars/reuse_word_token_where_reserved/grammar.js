// `if` is reserved everywhere except as an `alias` name, so in `alias = if ;` it's an identifier.
// Replacing `alias` with `let` makes it the reserved keyword, an error after `let =`. A reparse
// must not reuse the identifier there: it was lexed where `if` isn't reserved.

export default grammar({
    name: 'reuse_word_token_where_reserved',

    word: $ => $.identifier,

    reserved: {
        global: _ => ['if'],
        none: _ => [],
    },

    rules: {
        source_file: $ => repeat($._statement),
        _statement: $ => choice($.let_statement, $.alias_statement, $.if_statement),
        let_statement: $ => seq('let', '=', $.identifier, ';'),
        alias_statement: $ => seq('alias', '=', reserved('none', $.identifier), ';'),
        if_statement: $ => seq('if', $.identifier, ';'),
        identifier: _ => /[a-z]+/,
    },
});
