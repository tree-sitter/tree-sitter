export default grammar({
    name: 'epsilon_external_tokens',

    extras: $ => [/\s/],
    externals: $ => [$.zero_width],

    rules: {
        document: $ => seq($.zero_width, 'hello'),
    }
});