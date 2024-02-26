{
  "targets": [
    {
      "target_name": "tree_sitter_PARSER_NAME_binding",
      "dependencies": ["<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except"],
      "include_dirs": [
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
      ],
      "conditions": [
        ["OS=='mac'", {
            "cflags+": ["-fvisibility=hidden"],
            "xcode_settings": {
              "GCC_SYMBOLS_PRIVATE_EXTERN": "YES", # -fvisibility=hidden
            }
        }]
      ],
    }
  ]
}
