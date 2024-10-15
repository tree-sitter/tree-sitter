export default grammar({
  name: 'precedence_on_single_child_missing',

  rules: {
    expression: $ => choice($.function_call, $.identifier),

    function_call: $ => prec.right(choice(
      seq($.identifier, $.expression),
      seq($.identifier, $.block),
      seq($.identifier, $.expression, $.block),
    )),

    block: $ => seq('{', $.expression, '}'),

    identifier: _ => /[a-zA-Z]+/,
  },
});
