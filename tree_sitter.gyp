{
  'targets': [

    {
      'target_name': 'tree_sitter',
      'type': 'static_library',
      'include_dirs': [
        'include',
        'src',
      ],
      'sources': [
        '<!@(find include src -name "*.h" -or -name "*.cc" -or -name "*.c")',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
      },
      'direct_dependent_settings': {
        'include_dirs': ['include'],
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
      'target_name': 'compiler_specs',
      'type': 'executable',
      'dependencies': ['tree_sitter'],
      'include_dirs': [
        'src',
        'externals/bandit',
        'examples',
        'spec/compiler',
      ],
      'sources': [
        '<!@(find spec/compiler -name "*.h" -or -name "*.cc")',
        '<!@(find examples/grammars -name "*.hpp")',
      ],
    },

    {
      'target_name': 'runtime_specs',
      'type': 'executable',
      'dependencies': ['tree_sitter'],
      'include_dirs': [
        'src',
        'externals/bandit',
        'examples',
        'spec/runtime',
      ],
      'sources': [
        '<!@(find spec/runtime -name "*.h" -or -name "*.cc")',
        '<!@(find examples/parsers -name "*.c")',
      ],
    },
  ],

  'target_defaults': {
    'cflags': [
      '-Wall',
      '-Wextra',
      '-Wno-unused-parameter'
    ],
    'cflags_cc': [
      '-std=c++11',
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
