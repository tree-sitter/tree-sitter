// A comment that is a non-terminal extra, and a newline that the external scanner emits only where
// it's valid. In `( { a /*c*/` + newline + `} )`, the newline after the comment belongs to
// `statements`. A reparse that reuses a `statements` node ending at `a` would treat that newline as
// whitespace instead, and leave the comment outside `statements`.

export default grammar({
    name: 'reuse_before_extra_non_terminal',

    // `bang` is valid after `statements`, so the comment can't be reused there (its first leaf was
    // lexed where `newline` is valid too).
    externals: $ => [$.newline, $.bang],

    extras: $ => [/\s/, $.comment],

    rules: {
        program: $ => repeat($._item),
        _item: $ => choice($.block, $.list),
        block: $ => seq('{', optional($.statements), optional($.bang), '}'),
        // `statements` appear in both a block and a list, so their states merge, and inside a
        // block, `statements` is reduced on a `)` that turns out to be an error. Both allow a
        // `bang`, or the states would differ in external tokens and not merge.
        list: $ => seq('(', optional($.statements), optional($.bang), repeat($.block), ')'),
        statements: $ => seq($.statement, repeat(seq($.newline, $.statement)), optional($.newline)),
        statement: _ => /[a-z]+/,
        comment: _ => seq('/*', /[^*]+/, '*/'),
    }
});
