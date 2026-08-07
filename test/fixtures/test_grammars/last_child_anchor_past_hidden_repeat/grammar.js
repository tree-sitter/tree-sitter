// These three rules all parse to a flat run of `name` children, but `repeat`
// builds a different hidden `_repeat1` node for each of them, so a query's
// trailing `.` anchor has to walk past a different set of hidden nodes to
// decide whether a `name` is the last *named* child of its rule.
export default grammar({
  name: 'last_child_anchor_past_hidden_repeat',

  rules: {
    source_file: $ => repeat(choice($.trailing_sep, $.leading_sep, $.trailing_named)),

    // The hidden repeat ends with an anonymous node, and a named node follows it.
    trailing_sep: $ => seq('T', repeat(seq($.name, '.')), $.name),

    // The hidden repeat ends with a named node.
    leading_sep: $ => seq('L', $.name, repeat(seq('.', $.name))),

    // Same shape as `trailing_sep`, but a named node sits inside the repeat
    // ahead of the anonymous separator.
    trailing_named: $ => seq('N', repeat(seq($.name, $.tag, '.')), $.name),

    tag: _ => '!',

    name: _ => /[a-z]+/,
  }
});
