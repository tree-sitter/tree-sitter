// `param x` and `component x` end in the same merged state, which reduces `x` to a `type` when a
// `wildcard` follows, because a `param` allows one; so `_` is lexed as that keyword in both. After
// the reduction in a `component`, the keyword isn't valid, and the parser switches it to an
// identifier. In `param x _ ;`, the `wildcard` starts a `_declarator` node. Replacing `param` with
// `component` must not reuse that node: the switch only applies to a keyword leaf.

export default grammar({
    name: 'reuse_node_starting_with_keyword',

    word: $ => $.identifier,

    rules: {
        source_file: $ => repeat(choice($.param, $.component)),
        param: $ => seq('param', $.type, $._declarator, ';'),
        _declarator: $ => seq(choice($.identifier, $.wildcard), optional('[]')),
        component: $ => seq('component', $.type, $.identifier, ';'),
        type: $ => $.identifier,
        wildcard: _ => '_',
        identifier: _ => /[a-z_]+/,
    },
});
