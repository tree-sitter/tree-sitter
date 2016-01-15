{
  'targets': [
    {
      'target_name': 'tests',
      'type': 'executable',
      'dependencies': [
        'project.gyp:runtime',
        'project.gyp:compiler'
      ],
      'include_dirs': [
        'src',
        'spec',
        'externals/bandit',
        'externals/utf8proc',
      ],
      'sources': [
        'spec/specs.cc',
        '<!@(find spec/compiler -name "*.cc")',
        '<!@(find spec/runtime -name "*.cc")',
        '<!@(find spec/integration -name "*.cc")',
        '<!@(find spec/helpers -name "*.cc")',
      ],
      'libraries': [
        '-ldl'
      ],
      'default_configuration': 'Debug',
      'configurations': {'Debug': {}, 'Release': {}},
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
        '-std=c++0x',
      ],
      'ldflags': [
        '-g',
      ],
      'variables': {
        'USE_LIBPROFILER%': 'true',
      },
      'conditions': [
        ['USE_LIBPROFILER != "false"', {
          'libraries': ['-lprofiler'],
        }]
      ],
      'xcode_settings': {
        'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
        'OTHER_LDFLAGS': ['-g'],
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
