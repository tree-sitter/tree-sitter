// The repeated content ends in `eof()`, so it can match at most once, but it
// still has to consume some input to get there.
export default grammar({
    name: 'eof_repeat_via_rule',

    rules: {
      start: $ => $.body,
      body: $ => repeat1(seq($.b, eof())),
      b: _ => repeat1('a'),
    }
})
