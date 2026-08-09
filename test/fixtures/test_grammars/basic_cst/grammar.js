export default grammar({
  name: 'basic_cst',

  rules: {
    document: $ => $.assignment,

    assignment: $ => seq(
      field('name', $.identifier),
      '=',
      field('value', $.number),
    ),

    identifier: _ => /[a-z]+/,
    number: _ => /[0-9]+/,
  },
});
