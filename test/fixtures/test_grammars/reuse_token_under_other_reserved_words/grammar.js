// After `if`, identifiers use the global reserved words, and after `#`, the `none` set. The `do`
// keywords lex the same way under either, so when an edit replaces `if` with `#`, a reparse
// should reuse them. Keywords overlap the word token, so where it's valid, a keyword is reused
// only if it was lexed under the same lex state.

export default grammar({
    name: 'reuse_token_under_other_reserved_words',

    word: $ => $.identifier,

    reserved: {
        global: _ => ['if'],
        none: _ => [],
    },

    rules: {
        source_file: $ => choice(
            seq('if', repeat1(choice($.item, $.identifier))),
            seq('#', repeat1(choice($.item, reserved('none', $.identifier)))),
        ),
        item: _ => seq('do', ';'),
        identifier: _ => /[a-z]+/,
    },
});
