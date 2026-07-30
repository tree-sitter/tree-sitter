export default grammar({
  name: 'tokens_consuming_extra_interior',

  extras: _ => [/[ \t\n]/, /#[ab]*/],

  rules: {
    program: $ => choice($.s1, $.s2),
    s1: $ => seq('1', choice($.hash_ap, $.make)),
    hash_ap: _ => token('#ap'),
    make: _ => 'make',
    s2: $ => seq('2', choice($.hash_bq, $.zz)),
    hash_bq: _ => token('#bq'),
    zz: _ => 'zz',
  },
});
