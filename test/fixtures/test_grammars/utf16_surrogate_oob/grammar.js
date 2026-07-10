/// A minimal grammar for testing UTF-16 decode behavior.
/// The external scanner distinguishes surrogate code points (0xD800-0xDFFF)
/// from supplementary-plane characters (> 0xFFFF).
module.exports = grammar({
  name: 'utf16_surrogate_oob',

  externals: $ => [
    $.surrogate,
    $.supplementary,
  ],

  rules: {
    program: $ => repeat(choice(
      $.surrogate,
      $.supplementary,
    )),
  },
});
