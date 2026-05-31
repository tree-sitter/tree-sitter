export default grammar({
  name: "keyword_extraction_case_insensitive",

  word: ($) => $.variable,

  rules: {
    expression: ($) => choice($.variable, $.unary_expression),
    unary_expression: ($) => seq($.unary_command, $.expression),
    variable: ($) => token(prec(1, /[a-zA-Z_][a-zA-Z0-9_]*/)),
    unary_command: ($) =>
      token(prec(2, choice(/count/i, /creatediarylink/i))),
  },
});
