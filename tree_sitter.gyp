{
  'targets': [
    {
      'target_name': 'tree_sitter',
      'type': 'static_library',
      'include_dirs': [
        'include',
        'src/compiler',
        'src/runtime',
      ],
      'sources': [
        '<!@(find include src -name "*.h" -or -name "*.cpp")',
      ],
      'cflags_cc': [
        '-stdlib=libc++',
      ],
      'xcode_settings': {
        'CLANG_CXX_LIBRARY': 'libc++',
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
        'MACOSX_DEPLOYMENT_TARGET': '10.7',
      },
      'direct_dependent_settings': {
        'include_dirs': ['include'],
        'cflags_cc': [
          '-stdlib=libc++',
        ],
        'xcode_settings': {
          'CLANG_CXX_LIBRARY': 'libc++',

          # TODO - why don't specs build with this?
          # 'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },
      }
    },
    {
      'target_name': 'compiler_specs',
      'type': 'executable',
      'dependencies': ['tree_sitter'],
      'include_dirs': [
        'externals/bandit',
        'src/compiler',
        'spec',
      ],
      'sources': [
        '<!@(ls spec/*.h spec/*.cpp)',
        '<!@(find spec/compiler -name "*.h" -or -name "*.cpp")',
        '<!@(find examples/grammars -name "*.hpp")',
      ],
    },
    {
      'target_name': 'runtime_specs',
      'type': 'executable',
      'dependencies': ['tree_sitter'],
      'include_dirs': [
        'externals/bandit',
        'src/runtime',
        'spec',

        # TODO - make separate spec helpers for runtime and compiler specs
        'src/compiler',
      ],
      'sources': [
        '<!@(ls spec/*.h spec/*.cpp)',
        '<!@(find spec/runtime -name "*.h" -or -name "*.cpp")',
        '<!@(find examples/parsers -name "*.c")',
      ],
    },
  ],
  'target_defaults': {
    'cflags_cc': [
      '-std=c++11',
    ],
    'xcode_settings': {
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
    },
  }
}
