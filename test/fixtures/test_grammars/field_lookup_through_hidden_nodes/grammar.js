// Fields that reach a node through a hidden node. A tree cursor gives each node
// the innermost field on its way up to its visible parent, and so does
// `ts_node_string`; `ts_node_child_by_field_id` and negated fields in queries must
// agree with them.
export default grammar({
  name: 'field_lookup_through_hidden_nodes',

  supertypes: $ => [$.item],

  extras: $ => [/\s/, $.comment],

  rules: {
    source_file: $ => repeat(choice(
      $.list, $.binding, $.shadow, $.sum, $.aliased, $.alias_pair, $.multi, $.restored,
    )),

    // A field inside a supertype, below a hidden rule: in `[a, ...b]` the
    // spread is in the list's `spread` field.
    list: $ => seq('[', optional($._items), ']'),
    _items: $ => seq($.item, repeat(seq(',', $.item))),
    item: $ => choice($.name, field('spread', $.spread)),
    spread: $ => seq('...', $.name),

    aliased: $ => seq('alias', alias($.item, $.wrapped), ';'),
    alias_pair: $ => seq('pair', alias($.item, $.wrapped), ',', $.item, ';'),
    multi: $ => seq('multi', field('outer', $._shadowed), field('outer', $._binding), ';'),

    // A field on a hidden rule whose first node has a field of its own: in
    // `let a = b;` the first name is `inner`, and `outer` reaches `=` and `b`.
    binding: $ => seq('let', field('outer', $._binding), ';'),
    _binding: $ => seq(field('inner', $.name), '=', $.name),

    // A field on a hidden rule whose only node has a field of its own: in
    // `shadow a;` no node is `outer`.
    shadow: $ => seq('shadow', field('outer', $._shadowed), ';'),
    _shadowed: $ => field('inner', $.name),

    restored: $ => seq('restore', field('outer', $._restore), ';'),
    _restore: $ => field('inner', $._restored),
    _restored: $ => field('outer', $.name),

    // A left-recursive hidden rule: in `sum a + b + c;` the hidden `_sum`s
    // nest as deep as the sum is long, and `left` reaches `a`, the first `+`,
    // and `b`.
    sum: $ => seq('sum', $._sum, ';'),
    _sum: $ => choice($.name, seq(field('left', $._sum), '+', $.name)),

    name: _ => /[a-z0-9]+/,
    comment: _ => token(seq('//', /.*/)),
  },
});
