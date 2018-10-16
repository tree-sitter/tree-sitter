{
  'targets': [
    {
      'target_name': 'compiler',

      'type': 'static_library',
      'include_dirs': [
        'include',
        'src',
        'externals/utf8proc',
        'externals/json-parser',
      ],
      'sources': [
        'src/compiler/build_tables/lex_item.cc',
        'src/compiler/build_tables/lex_item_transitions.cc',
        'src/compiler/build_tables/lex_table_builder.cc',
        'src/compiler/build_tables/lookahead_set.cc',
        'src/compiler/build_tables/parse_item.cc',
        'src/compiler/build_tables/parse_item_set_builder.cc',
        'src/compiler/build_tables/parse_table_builder.cc',
        'src/compiler/build_tables/property_table_builder.cc',
        'src/compiler/build_tables/rule_can_be_blank.cc',
        'src/compiler/compile.cc',
        'src/compiler/generate_code/c_code.cc',
        'src/compiler/generate_code/property_table_json.cc',
        'src/compiler/lex_table.cc',
        'src/compiler/log.cc',
        'src/compiler/parse_json.cc',
        'src/compiler/parse_table.cc',
        'src/compiler/precedence_range.cc',
        'src/compiler/prepare_grammar/expand_repeats.cc',
        'src/compiler/prepare_grammar/expand_tokens.cc',
        'src/compiler/prepare_grammar/extract_choices.cc',
        'src/compiler/prepare_grammar/extract_simple_aliases.cc',
        'src/compiler/prepare_grammar/extract_tokens.cc',
        'src/compiler/prepare_grammar/flatten_grammar.cc',
        'src/compiler/prepare_grammar/intern_symbols.cc',
        'src/compiler/prepare_grammar/normalize_rules.cc',
        'src/compiler/prepare_grammar/parse_regex.cc',
        'src/compiler/prepare_grammar/prepare_grammar.cc',
        'src/compiler/prepare_grammar/token_description.cc',
        'src/compiler/rule.cc',
        'src/compiler/syntax_grammar.cc',
        'src/compiler/rules/character_set.cc',
        'src/compiler/rules/choice.cc',
        'src/compiler/rules/metadata.cc',
        'src/compiler/rules/repeat.cc',
        'src/compiler/rules/seq.cc',
        'src/compiler/util/string_helpers.cc',
        'externals/utf8proc/utf8proc.c',
        'externals/json-parser/json.c',
      ],
      'cflags_cc': [
        '-std=c++14',
      ],
      'xcode_settings': {
        'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
      },
      'direct_dependent_settings': {
        'include_dirs': [
          'include'
        ],
      },

      # Mac OS has an old version of libstdc++ that doesn't support c++11.
      # libc++ is only present on 10.7 and later.
      'conditions': [
        ['OS == "mac"', {
          'cflags_cc': [ '-stdlib=libc++' ],
          'xcode_settings': {
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
          },
          'direct_dependent_settings': {
            'cflags_cc': [ '-stdlib=libc++' ],
            'xcode_settings': {
              'CLANG_CXX_LIBRARY': 'libc++',
            },
          },
        }]
      ],
    },

    {
      'target_name': 'runtime',
      'type': 'static_library',
      'include_dirs': [
        'include',
        'src',
        'externals/utf8proc',
      ],
      'sources': [
        'src/runtime/get_changed_ranges.c',
        'src/runtime/language.c',
        'src/runtime/lexer.c',
        'src/runtime/node.c',
        'src/runtime/stack.c',
        'src/runtime/parser.c',
        'src/runtime/subtree.c',
        'src/runtime/tree.c',
        'src/runtime/tree_cursor.c',
        'src/runtime/utf16.c',
        'externals/utf8proc/utf8proc.c',
      ],
      'cflags_c': [
        '-std=c99', '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=1'
      ],
      'ldflags': [
        '-g',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'include'
        ],
      },
    },
  ],

  'target_defaults': {
    'default_configuration': 'Release',
    'configurations': {
      'Debug': {
        'cflags': [ '-g' ],
        'ldflags': [ '-g' ],
        'xcode_settings': {
          'ARCHS': ['x86_64'],
          'OTHER_LDFLAGS': ['-g'],
          'GCC_OPTIMIZATION_LEVEL': '0',
        },
      },
      'Test': {
        'defines': ['TREE_SITTER_TEST=true'],
        'cflags': [ '-g' ],
        'ldflags': [ '-g' ],
        'xcode_settings': {
          'ARCHS': ['x86_64'],
          'OTHER_LDFLAGS': ['-g'],
          'GCC_OPTIMIZATION_LEVEL': '0',
          'OTHER_CPLUSPLUSFLAGS': ['-fsanitize=address'],
        },
      },
      'Fuzz': {
        'cflags': ['<!@(echo $CFLAGS)'],
        'ldflags': ['<!@(echo $CFLAGS)'],
      },
      'Release': {
        'cflags': [ '-O2', '-fno-strict-aliasing' ],
        'cflags!': [ '-O3', '-fstrict-aliasing' ],
        'xcode_settings': {
          'ARCHS': ['x86_64'],
        },
      },
    },

    'cflags': [
      '-Wall',
      '-Wextra',
      '-Wno-unused-parameter'
    ],

    'defines': ['UTF8PROC_STATIC'],

    'xcode_settings': {
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
      'WARNING_CFLAGS': [
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter'
      ],
    },

    # For 64-bit builds on appveyor, we need to explicitly tell gyp
    # to generate an x64 target in the MSVS project file.
    'conditions': [
      ['"<!(echo %PLATFORM%)" == "x64"', {
        'msvs_configuration_platform': 'x64',
      }]
    ]
  }
}
