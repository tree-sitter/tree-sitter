// A repeat item ending in `eof()` can match at most once. The EOF-gated
// reduce must survive table minimization, so a second `text` is a parse
// error rather than being silently accepted.
export default grammar({
    name: 'eof_repeat_terminated',

    rules: {
        source_file: $ => repeat(seq('text', eof())),
    }
});
