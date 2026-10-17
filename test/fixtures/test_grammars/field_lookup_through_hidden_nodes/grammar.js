// Fields that reach a node through a hidden node. A tree cursor gives each node
// the innermost field on its way up to its visible parent, and so does
// `ts_node_string`; `ts_node_child_by_field_id` and negated fields in queries must
// agree with them.
export default grammar({
  name: 'field_lookup_through_hidden_nodes',

  supertypes: $ => [$.item],

  extras: $ => [/\s/, $.comment, $._note],

  rules: {
    source_file: $ => repeat(choice(
      $.list, $.binding, $.shadow, $.sum, $.aliased, $.alias_pair, $.multi, $.restored,
      $.back, $.maybe, $.order, $.skip,
    )),

    // A field inside a supertype, below a hidden rule: in `[a, ...b]` the
    // spread is in the list's `spread` field.
    list: $ => seq('[', optional($._items), ']'),
    _items: $ => seq($.item, repeat(seq(',', $.item))),
    item: $ => choice($.name, field('spread', $.spread)),
    spread: $ => seq('...', $.name),

    aliased: $ => seq('alias', alias($.item, $.wrapped), ';'),
    alias_pair: $ => seq('pair', alias($.item, $.wrapped), ',', $.item, ';'),

    // The same field on two hidden rules: in `multi a a = b;` the first has no
    // `outer` node, since its only name is `inner`, so `outer` reaches the `=`
    // and `b` of the second.
    multi: $ => seq('multi', field('outer', $._shadowed), field('outer', $._binding), ';'),

    // A field on a hidden rule whose first node has a field of its own: in
    // `let a = b;` the first name is `inner`, and `outer` reaches `=` and `b`.
    binding: $ => seq('let', field('outer', $._binding), ';'),
    _binding: $ => seq(field('inner', $.name), '=', $.name),

    // A field on a hidden rule whose only node has a field of its own: in
    // `shadow a;` no node is `outer`.
    shadow: $ => seq('shadow', field('outer', $._shadowed), ';'),
    _shadowed: $ => field('inner', $.name),

    // A field inside a field inside the same field: in `restore a;` the name is
    // `outer`, its innermost field.
    restored: $ => seq('restore', field('outer', $._restore), ';'),
    _restore: $ => field('inner', $._restored),
    _restored: $ => field('outer', $.name),

    // A field on a hidden rule that starts with a hidden rule without it: in
    // `back a b;` the first name is `inner`, so `outer` reaches only the second.
    back: $ => seq('back', field('outer', $._back), ';'),
    _back: $ => seq($._shadowed, $.name),

    // A field on a hidden rule that can hold the same field, but doesn't here:
    // in `maybe none end;` no node is `outer`, while in `maybe a end;` the name
    // is.
    maybe: $ => seq('maybe', field('outer', $._maybe), ';'),
    _maybe: $ => field('inner', $._maybe_inner),
    _maybe_inner: $ => seq($._opt, 'end'),
    _opt: $ => choice(field('outer', $.name), 'none'),

    // Fields out of alphabetical order inside a hidden rule: in `order a b c;`
    // the first two names are `zeta` and `alpha`, so `outer` reaches the third.
    order: $ => seq('order', field('outer', $._order), ';'),
    _order: $ => seq(field('zeta', $.name), field('alpha', $.name), $.name),

    // A hidden child in another field, then a name with a field of its own: in
    // `skip a b c;` `outer` reaches only the third name.
    skip: $ => seq('skip', field('outer', $._skip), ';'),
    _skip: $ => seq(field('inner', $._shadowed), field('other', $.name), $.name),

    // A left-recursive hidden rule: in `sum a + b + c;` the hidden `_sum`s
    // nest as deep as the sum is long, and `left` reaches `a`, the first `+`,
    // and `b`.
    sum: $ => seq('sum', $._sum, ';'),
    _sum: $ => choice($.name, seq(field('left', $._sum), '+', $.name)),

    name: _ => /[a-z0-9]+/,
    comment: _ => token(seq('//', /.*/)),

    // A hidden extra that sets a field inside itself: in `let a @x = b;` the
    // name after `@` is `outer`, and comes before the `=`.
    _note: $ => seq('@', field('outer', $.name)),
  },
});
