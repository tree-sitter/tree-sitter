// The `eof()` alternative of `terminator` is unreachable inside the parens
// (because `)` always has to come after) so the generator silently drops
// that production. The grammar still parses because the newline and `;`
// alternatives remain.

const terminator = choice('\n', ';', eof());

export default grammar({
    name: 'eof_dropped_branch',

    rules: {
        source_file: $ => seq(
            '(',
            optional(seq($.item, repeat(seq(terminator, $.item)), optional(terminator))),
            ')',
        ),

        item: _ => 'x',
    }
});
