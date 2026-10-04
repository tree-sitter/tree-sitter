export default grammar({
  name: "depends_on_column_failed_scan",
  externals: ($) => [$.head],
  extras: () => [],
  rules: {
    document: ($) => repeat(choice($.head, $.tail, $.letter, $.newline)),
    tail: () => "x",
    letter: () => "a",
    newline: () => "\n",
  },
});
