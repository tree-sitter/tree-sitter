{
  "targets": [
    {
      "target_name": "tree_sitter_PARSER_NAME_binding",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "src",
      ],
      "sources": [
        "bindings/node/binding.cc",
        "src/parser.c",
        # NOTE: if your language has an external scanner, add it here.
      ],
      "cflags_c": [
        "-std=c11",
      ],
      "cflags_cc": [
        "-Wno-cast-function-type",
      ]
    }
  ]
}
