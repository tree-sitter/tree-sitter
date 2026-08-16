export default grammar({
    name: 'eof_misplaced',

    rules: {
        source_file: $ => seq(eof(), 'after'),
    }
});
