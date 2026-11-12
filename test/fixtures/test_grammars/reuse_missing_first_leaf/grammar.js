// In `; < b >`, error recovery inserts a missing identifier after `;`: as an `expr`, it would let
// `<` be reduced. The `call` interpretation then wins. Replacing `;` with `!` makes a `call`
// valid there again. A reparse that reused that `call` would shift its missing identifier as a
// real token, instead of parsing `! < b >` as a `tagged` without a `call`.

export default grammar({
    name: 'reuse_missing_first_leaf',

    // An identifier followed by `<` starts either a `call` or a `compare`.
    conflicts: $ => [[$.call, $.expr]],

    rules: {
        source_file: $ => repeat($._item),
        _item: $ => choice($.call, $.compare, $.tagged, $.stop),
        // Reduced once the conflict is settled, by a single stack version, so nothing else makes
        // it fragile.
        call: $ => seq($.identifier, '<', $.identifier, '>'),
        compare: $ => seq($.expr, '<', $.expr),
        expr: $ => $.identifier,
        // After `!`, both an identifier (starting a `call`) and `<` are valid.
        tagged: $ => seq('!', choice($.call, seq('<', $.identifier, '>'))),
        stop: _ => ';',
        identifier: _ => /[a-z]+/,
    },
});
