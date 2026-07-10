export default grammar({
    name: 'wasm_realloc_clobber_region',

    extras: _ => [/\s/],
    externals: $ => [$.zero_width],

    rules: {
        document: $ => seq($.zero_width, 'hello'),
    }
});
