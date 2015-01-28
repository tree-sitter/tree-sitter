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
        'spec',
        'externals/bandit',
      ],
      'sources': [
        '<!@(find spec/compiler -name "*.cc")',
        '<!@(find spec/fixtures/grammars -name "*.cc")',
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
        'externals/utf8proc',
      ],
      'sources': [
        '<!@(find spec/runtime -name "*.cc")',
        '<!@(find spec/fixtures/parsers -name "*.c")',
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
    'default_configuration': 'Debug',
    'configurations': {'Debug': {}},

    'cflags': [
      '-g',
      '-O0',
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

    'libraries': ['-weak-lprofiler'],

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
