export default grammar({
  name: 'tokens_with_divergent_separator_prefixes',

  extras: _ => [/\s/],

  rules: {
    program: $ => choice($.a, $.b, $.c),
    a: $ => seq('1', choice($.ap, $.make)),
    ap: _ => token(seq(' ', 'p')),
    make: _ => 'make',
    b: $ => seq('2', choice($.bq, $.zz)),
    zz: _ => 'zz',
    bq: _ => token(seq(' ', '\n', 'q')),
    c: $ => seq('3', $.tabz),
    tabz: _ => token(seq('\t', 'z')),
  },
});
