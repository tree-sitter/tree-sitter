export default grammar({
  name: 'immediate_tokens_only',

  rules: {
    source_file: $ => repeat1(alias(token.immediate('x'), $.x)),
  },
});
