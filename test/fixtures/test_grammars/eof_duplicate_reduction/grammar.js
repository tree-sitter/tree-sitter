// Both branches reduce `line` to the same single `'text'` child, differing only in
// whether the reduce is gated on end of input. Identical actions are not a conflict,
// but they still have to be compared on precedence rather than skipped.
export default grammar({
    name: 'eof_duplicate_reduction',

    rules: {
        source_file: $ => repeat($.line),
        line: _ => choice('text', seq('text', eof())),
    }
});
