// A field on a hidden rule belongs to every node inside the rule that has no
// field of its own, so a node can share its field with later siblings that the
// field map of its parent does not list.
export default grammar({
  name: 'field_on_hidden_rule',

  rules: {
    source_file: $ => repeat(choice($.binding, $.sum)),

    // `outer` reaches the `=` and the second name, but not the first name,
    // which has a field of its own.
    binding: $ => seq('let', field('outer', $._binding), ';'),
    _binding: $ => seq(field('inner', $.name), '=', $.name),

    // A `_sum` in the `left` of another passes `left` on, so in `a + b + c` it
    // reaches `a`, the first `+`, and `b`.
    sum: $ => seq('sum', $._sum, ';'),
    _sum: $ => choice($.name, seq(field('left', $._sum), '+', $.name)),

    name: _ => /[a-z]+/,
  }
});
