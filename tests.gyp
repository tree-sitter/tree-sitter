{
  'targets': [
    {
      'target_name': 'compiler_specs',
      'type': 'executable',
      'dependencies': [
        'project.gyp:compiler'
      ],
      'include_dirs': [
        'src',
        'examples',
        'spec',
        'externals/bandit',
      ],
      'sources': [
        '<!@(find spec/compiler examples/grammars -name "*.cc")',
      ],
    },

    {
      'target_name': 'runtime_specs',
      'type': 'executable',
      'dependencies': [
        'project.gyp:runtime'
      ],
      'include_dirs': [
        'src',
        'examples',
        'spec',
        'externals/bandit',
      ],
      'sources': [
        '<!@(find spec/runtime -name "*.cc" -or -name "*.c")',
        '<!@(find examples/parsers -name "*.c")',
      ],
      'variables': {
        'USE_BOOST_REGEX%': 'false',
      },
      'conditions': [
        ['USE_BOOST_REGEX != "false"', {
          'defines': ['USE_BOOST_REGEX'],
          'libraries': ['-lboost_regex'],
        }]
      ],
    },
  ],

  'target_defaults': {
    'cflags': [
      '-Wall',
      '-Wextra',
      '-Wno-unused-parameter',
      '-Wno-unknown-pragmas',
    ],
    'cflags_c': [
      '-std=c99'
    ],
    'cflags_cc': [
      '-std=c++0x',
    ],
    'xcode_settings': {
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
      'WARNING_CFLAGS': [
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter'
      ],
    },
  }
}

