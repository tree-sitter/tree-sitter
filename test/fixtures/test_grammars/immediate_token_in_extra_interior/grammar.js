export default grammar({
  name: 'immediate_token_in_extra_interior',

  extras: _ => [/[ \t\n]/, /#[ab]*/],

  rules: {
    program: $ => choice($.s1, $.s2),
    s1: $ => seq('1', $.imm_marker),
    // Reaches an extra's interior, but is not itself matched by the extra:
    // a token the comment matches whole conflicts with it on other grounds.
    imm_marker: _ => token.immediate('#ax'),
    s2: $ => seq('2', choice($.hash_z, $.make)),
    hash_z: _ => token('#z'),
    make: _ => 'make',
  },
});
