export default grammar({
  name: 'no_internal_tokens_with_extras',

  externals: $ => [$.a, $.b],

  rules: {
    source_file: $ => repeat(choice($.a, $.b)),
  },
});
