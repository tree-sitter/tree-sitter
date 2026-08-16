// `a` has two productions that reduce identically and differ only in precedence.
// The higher one has to outrank `c`, which means the duplicate action still has
// to be compared against rather than skipped.
export default grammar({
    name: 'duplicate_reduction_precedence',

    rules: {
        start: $ => choice($.a, $.c),
        a: $ => choice($.x, prec(2, $.x)),
        c: $ => $.x,
        x: _ => 'x',
    }
})
