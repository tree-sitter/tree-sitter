// External scanner whose token choice depends on `lexer->eof()`: at a
// '`' it peeks past mark_end for a matching close, emitting open_delim
// if one is found or unclosed_delim if eof is reached first. Inside an
// open span the same '`' is emitted as close_delim.

export default grammar({
    name: 'external_lookahead_eof_boundary',

    externals: $ => [$.open_delim, $.close_delim, $.unclosed_delim],

    rules: {
        document: $ => repeat(choice($.span, $.unclosed_delim)),
        span: $ => seq($.open_delim, $.close_delim),
    }
});
