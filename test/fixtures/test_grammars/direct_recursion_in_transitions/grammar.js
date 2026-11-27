export default grammar({
  name: 'direct_recursion_in_transitions',

  rules: {
    source_file: $ => choice($.source_file, 'a'),
  },
});
