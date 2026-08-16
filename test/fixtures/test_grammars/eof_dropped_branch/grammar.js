// The `eof()` alternative of `terminator` is unreachable inside the parens
// (because `)` always has to come after) so the generator silently drops
// that production. The grammar still parses because the newline and `;`
// alternatives remain.

const terminator = choice('\n', ';', eof());

export default grammar({
    name: 'eof_dropped_branch',

    inline: $ => [$._inline_eof],

    rules: {
        source_file: $ => choice(
            seq(
                '(',
                optional(seq($.item, repeat(seq(terminator, $.item)), optional(terminator))),
                ')',
            ),
            $.inline_test,
        ),

        item: _ => 'x',

        // Inlining the second alternative would put `bad` after EOF, so that
        // alternative must be discarded while the reachable one remains.
        inline_test: $ => choice('ok', seq($._inline_eof, 'bad')),
        _inline_eof: _ => eof(),
    }
});
