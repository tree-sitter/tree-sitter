export default grammar({
  name: 'immediate_token_on_separator_char',

  extras: _ => [/[ \t\n]/],

  rules: {
    program: $ => choice($.s1, $.s2),
    s1: $ => seq('1', $.imm_space),
    imm_space: _ => token.immediate(' p'),
    s2: $ => seq('2', choice($.zz, $.make)),
    zz: _ => 'zz',
    make: _ => 'make',
  },
});
