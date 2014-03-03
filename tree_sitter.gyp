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
    },
    {
      'target_name': 'compiler_specs',
      'type': 'executable',
      'dependencies': ['tree_sitter'],
      'include_dirs': [
        'include',
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
        'include',
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
    'xcode_settings': {
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
      'CLANG_CXX_LIBRARY': 'libc++',
    },
  },
}
