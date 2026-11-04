export default grammar({
  name: 'reserved_word_merging',
  word: $ => $.identifier,
  reserved: {
    global: _ => ['if'],
    empty: _ => [],
  },
  rules: {
    source: $ => repeat(choice($.c, $.a, $.b, $.if)),
    a: $ => seq('a', $.value, $.label),      // label: keywords allowed
    b: $ => seq('b', $.value, $.identifier), // identifier: keywords reserved
    c: $ => seq('c', $.value, ';'),
    label: $ => reserved('empty', $.identifier),
    value: _ => seq('(', ')'),
    if: _ => seq('if', ';'),
    identifier: _ => /[a-z]+/,
  },
});
