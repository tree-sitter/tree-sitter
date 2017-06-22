{
  'targets': [
    {
      'target_name': 'benchmarks',
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
      'configurations': {'Test': {}, 'Release': {}},
      'default_configuration': 'Release',
      'xcode_settings': {'CLANG_CXX_LANGUAGE_STANDARD': 'c++11'},
      'cflags_cc': ['-std=c++11'],
    },
    {
      'target_name': 'tests',
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
        'test/tests.cc',
        '<!@(find test/compiler -name "*.cc")',
        '<!@(find test/runtime -name "*.cc")',
        '<!@(find test/integration -name "*.cc")',
        '<!@(find test/helpers -name "*.cc")',
      ],
      'libraries': [
        '-ldl'
      ],
      'default_configuration': 'Test',
      'configurations': {'Test': {}, 'Release': {}},
      'cflags': [
        '-g',
        '-O0',
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter',
        '-Wno-unknown-pragmas',
      ],
      'cflags_c': [
        '-std=c99',
      ],
      'cflags_cc': [
        '-std=c++14',
      ],
      'ldflags': [
        '-g',
      ],
      'xcode_settings': {
        'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
        'OTHER_LDFLAGS': ['-g'],
        'OTHER_CPLUSPLUSFLAGS': ['-fsanitize=address'],
        'GCC_OPTIMIZATION_LEVEL': '0',
        'ALWAYS_SEARCH_USER_PATHS': 'NO',
        'WARNING_CFLAGS': [
          '-Wall',
          '-Wextra',
          '-Wno-unused-parameter'
        ],
      },
    }
  ]
}
