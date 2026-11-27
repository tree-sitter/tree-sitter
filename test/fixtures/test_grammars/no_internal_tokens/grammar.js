export default grammar({
  name: 'no_internal_tokens',

  extras: _ => [],
  externals: $ => [$.a, $.b],

  rules: {
    source_file: $ => repeat(choice($.a, $.b)),
  },
});
