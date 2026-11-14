// The keyword `k` is reserved wherever an identifier is valid, and it's listed in `externals`, so
// the external scanner knows where `k` is valid. There, the scanner also lexes `x` as `k`. After
// `( )`, two states share a core: one reduces `x_node` on `k`, and the other on an identifier,
// where `k` is reserved but not valid. Merging them would tell the scanner that `k` is valid in the
// second, which would turn the `x` in `b ( ) x` into `k`.

export default grammar({
    name: 'reserved_external_twin',

    externals: _ => ['k'],

    extras: _ => [/\s/],

    word: $ => $.identifier,

    reserved: {
        global: _ => ['k'],
    },

    rules: {
        source_file: $ => choice(
            seq('a', $.x_node, 'k'),
            seq('b', $.x_node, $.identifier),
        ),

        x_node: _ => seq('(', ')'),

        identifier: _ => /[a-z]+/,
    },
});
