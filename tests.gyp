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
        'test/tests.cc',
        '<!@(find test/compiler -name "*.cc")',
        '<!@(find test/runtime -name "*.cc")',
        '<!@(find test/integration -name "*.cc")',
        '<!@(find test/helpers -name "*.cc")',
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
