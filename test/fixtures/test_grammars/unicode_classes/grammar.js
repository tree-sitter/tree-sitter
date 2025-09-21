export default grammar({
  name: 'unicode_classes',

  externals: $ => [$.letter_number_with_prefix],

  rules: {
    program: $ => repeat(choice(
      $.lower,
      $.upper,
      $.math_sym,
      $.letter_number,
      $.letter_number_with_prefix,
    )),

    lower: _ => /\p{Ll}\p{L}*/,

    upper: _ => /\p{Lu}\p{L}*/,

    math_sym: _ => /\p{Sm}+/,

    letter_number: _ => /\p{Letter_Number}/,
  },
});
