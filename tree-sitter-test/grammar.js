/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "test",

  externals: $ => [
    $._equals_begin,
    $._equals_end,
    $._dashes,
  ],

  extras: _ => [],

  rules: {
    file: $ => repeat(
      choice($.test, $._eol)
    ),

    test: $ => prec.right(seq(
      $.header,
      alias($._body, $.input),
      alias($._dashes, $.separator),
      optional(alias($._body, $.output)),
    )),

    _line: _ => /[^\r\n]+/,

    _body: $ => repeat1(choice($._line, $._eol)),

    header: $ => seq(
      alias($._equals_begin, $.separator),
      alias($._line, $.name),
      $._eol,
      optional($.attributes),
      alias($._equals_end, $.separator),
    ),

    attributes: $ => repeat1(
      choice($.attribute, $._eol)
    ),

    attribute: $ => choice(
      ":skip",
      ":error",
      ":fail-fast",
      $._language,
      $._platform,
    ),

    _language: $ => seq(
      ":language",
      "(",
      field("language", alias($._lang, $.parameter)),
      ")"
    ),

    _platform: $ => seq(
      ":platform",
      "(",
      field("platform", alias($._os, $.parameter)),
      ")"
    ),

    _lang: _ => token(repeat1(/[\w.-]/)),

    _os: _ => token(choice(
      "linux",
      "macos",
      "ios",
      "freebsd",
      "dragonfly",
      "netbsd",
      "openbsd",
      "solaris",
      "android",
      "windows",
    )),

    _eol: _ => /[\r\n]|\r\n/
  }
});
