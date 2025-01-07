// This is a partial extraction of the clojure grammar found at
// https://github.com/sogaiu/tree-sitter-clojure

function regex(...patts) {
  return RegExp(patts.join(""));
}

const WHITESPACE_CHAR = regex(
  "[",
  "\\f\\n\\r\\t, ",
  "\\u000B\\u001C\\u001D\\u001E\\u001F",
  "\\u2028\\u2029\\u1680",
  "\\u2000\\u2001\\u2002\\u2003\\u2004\\u2005\\u2006\\u2008",
  "\\u2009\\u200a\\u205f\\u3000",
  "]",
);

const WHITESPACE = token(repeat1(WHITESPACE_CHAR));

const SYMBOL_HEAD = regex(
  "[^",
  "\\f\\n\\r\\t ",
  "/",
  "()\\[\\]{}",
  '"',
  "@~^;`",
  "\\\\",
  ",:#'0-9",
  "\\u000B\\u001C\\u001D\\u001E\\u001F",
  "\\u2028\\u2029\\u1680",
  "\\u2000\\u2001\\u2002\\u2003\\u2004\\u2005\\u2006\\u2008",
  "\\u2009\\u200a\\u205f\\u3000",
  "]",
);

const SYMBOL_BODY = choice(SYMBOL_HEAD, regex("[:#'0-9]"));

const SYMBOL = token(seq(SYMBOL_HEAD, repeat(SYMBOL_BODY)));

module.exports = grammar({
  name: "missing_next_named_sibling",

  extras: ($) => [],

  conflicts: ($) => [],

  rules: {
    source: ($) => repeat(choice($._form, $._gap)),

    _ws: ($) => WHITESPACE,
    _gap: ($) => choice($._ws),

    _form: ($) => choice($.sym_lit, $.list_lit),

    _sym_unqualified: ($) => field("name", alias(choice(SYMBOL), $.sym_name)),
    sym_lit: ($) => seq(choice($._sym_unqualified)),

    _bare_list_lit: ($) =>
      seq(
        field("open", "("),
        repeat(choice(field("value", $._form), $._gap)),
        field("close", ")"),
      ),
    list_lit: ($) => seq($._bare_list_lit),
  },
});
