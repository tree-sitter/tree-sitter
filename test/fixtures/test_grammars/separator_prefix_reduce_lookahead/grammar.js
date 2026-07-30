export default grammar({
  name: 'separator_prefix_reduce_lookahead',

  extras: _ => [/[ \t\n]/],

  rules: {
    program: $ =>
      choice(
        seq('a', $.item, alias(token(seq(/\s*/, ':')), ':'), 'x'),
        seq('b', $.item, 'y'),
      ),
    item: _ => seq('i', 'j'),
  },
});
