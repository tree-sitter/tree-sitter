export default grammar({
    name: 'eof_basic',

    rules: {
        source_file: $ => repeat($.line),

        line: $ => choice(
            seq('text', '\n'),
            seq('text', eof()),
        ),
    }
});
