{
  'targets': [
    {
      'target_name': 'benchmarks',
      'default_configuration': 'Release',
      'type': 'executable',
      'dependencies': [
        'project.gyp:runtime',
        'project.gyp:compiler'
      ],
      'include_dirs': [
        'src',
        'test',
        'externals/utf8proc',
      ],
      'sources': [
        'test/benchmarks.cc',
        'test/helpers/file_helpers.cc',
        'test/helpers/load_language.cc',
        'test/helpers/read_test_entries.cc',
        'test/helpers/stderr_logger.cc',
      ],
    },
    {
      'target_name': 'tests',
      'default_configuration': 'Test',
      'type': 'executable',
      'dependencies': [
        'project.gyp:runtime',
        'project.gyp:compiler'
      ],
      'include_dirs': [
        'src',
        'test',
        'externals/bandit',
        'externals/utf8proc',
        'externals/crypto-algorithms',
      ],
      'sources': [
        'test/compiler/build_tables/lex_conflict_manager_test.cc',
        'test/compiler/build_tables/lex_item_test.cc',
        'test/compiler/build_tables/lex_table_builder_test.cc',
        'test/compiler/build_tables/parse_item_set_builder_test.cc',
        'test/compiler/build_tables/rule_can_be_blank_test.cc',
        'test/compiler/prepare_grammar/expand_repeats_test.cc',
        'test/compiler/prepare_grammar/expand_tokens_test.cc',
        'test/compiler/prepare_grammar/extract_choices_test.cc',
        'test/compiler/prepare_grammar/extract_tokens_test.cc',
        'test/compiler/prepare_grammar/flatten_grammar_test.cc',
        'test/compiler/prepare_grammar/intern_symbols_test.cc',
        'test/compiler/prepare_grammar/parse_regex_test.cc',
        'test/compiler/rules/character_set_test.cc',
        'test/compiler/rules/choice_test.cc',
        'test/compiler/rules/repeat_test.cc',
        'test/compiler/util/string_helpers_test.cc',
        'test/helpers/encoding_helpers.cc',
        'test/helpers/file_helpers.cc',
        'test/helpers/load_language.cc',
        'test/helpers/point_helpers.cc',
        'test/helpers/random_helpers.cc',
        'test/helpers/read_test_entries.cc',
        'test/helpers/record_alloc.cc',
        'test/helpers/scope_sequence.cc',
        'test/helpers/spy_input.cc',
        'test/helpers/spy_logger.cc',
        'test/helpers/stderr_logger.cc',
        'test/helpers/stream_methods.cc',
        'test/helpers/tree_helpers.cc',
        'test/integration/fuzzing-examples.cc',
        'test/integration/real_grammars.cc',
        'test/integration/test_grammars.cc',
        'test/runtime/document_test.cc',
        'test/runtime/language_test.cc',
        'test/runtime/node_test.cc',
        'test/runtime/parser_test.cc',
        'test/runtime/stack_test.cc',
        'test/runtime/tree_test.cc',
        'test/tests.cc',
      ],
      'cflags': [
        '-g',
        '-O0',
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter',
        '-Wno-unknown-pragmas',
      ],
      'ldflags': ['-g'],
      'xcode_settings': {
        'OTHER_LDFLAGS': ['-g'],
        'OTHER_CPLUSPLUSFLAGS': ['-fsanitize=address'],
        'GCC_OPTIMIZATION_LEVEL': '0',
        'WARNING_CFLAGS': [
          '-Wall',
          '-Wextra',
          '-Wno-unused-parameter'
        ],
      },
    }
  ],

  'target_defaults': {
    'configurations': {'Test': {}, 'Release': {}},
    'cflags_cc': ['-std=c++14'],
    'libraries': ['-ldl'],
    'xcode_settings': {
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
    }
  }
}
