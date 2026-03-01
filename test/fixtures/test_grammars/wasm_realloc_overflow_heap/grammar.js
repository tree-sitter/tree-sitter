export default grammar({
    name: 'wasm_realloc_overflow_heap',

    extras: _ => [/\s/],
    externals: $ => [$.zero_width],

    rules: {
        document: $ => seq($.zero_width, 'hello'),
    }
});
