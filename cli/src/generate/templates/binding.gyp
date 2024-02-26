{
  "targets": [
    {
      "target_name": "tree_sitter_PARSER_NAME_binding",
      "dependencies": ["<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except"],
      "include_dirs": [
        "src"
      ],
      "sources": [
        "bindings/node/binding.cc",
        "src/parser.c",
        # If your language uses an external scanner, add it here.
      ],
      "cflags_c": [
        "-std=c99",
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
