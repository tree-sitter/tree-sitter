// `n` matches the empty string, so `seq($.n, eof())` can match nothing at all at
// the end of input and the outer `repeat` would spin.
export default grammar({
    name: 'eof_repeat_via_nullable_rule',

    rules: {
        start: $ => $.body,
        body: $ => repeat1(seq($.n, eof())),
        n: _ => optional('a'),
    }
})
