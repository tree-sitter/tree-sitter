module.exports = grammar({
  name: 'anonymous_error',
  rules: {
    document: $ => repeat(choice('ok', 'ERROR')),
  }
});
