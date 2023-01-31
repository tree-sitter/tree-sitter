// This grammar has an external scanner whose `scan` method sets the
// `force_serialize_state` flag to ensure that the state is serialized, even
// though `scan` returns false for the first two tokens.

module.exports = grammar({
    name: "external_force_serialize",

    externals: $ => [
        $.external
    ],

    rules: {
        root: $ => seq(
            $.internal_or_external,
            $.internal_or_external,
            $.internal_or_external,
        ),
        internal_or_external: $ => choice($.internal, $.external),
        internal: $ => /[a-z]+/
    }
})
