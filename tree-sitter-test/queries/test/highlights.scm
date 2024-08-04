(name) @markup.heading

[
  ":skip"
  ":error"
  ":fail-fast"
  ":language"
  ":platform"
] @attribute

(attribute
  language: (parameter) @string)

(attribute
  platform: (parameter) @constant.builtin)

((test
  (separator) @punctuation.delimiter)
  (#set! conceal ""))

((header
  (separator) @punctuation.delimiter)
  (#set! conceal ""))

[
  "("
  ")"
] @punctuation.bracket
