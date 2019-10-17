ts_public_headers = []
ts_sources = []

ts_include_directories = []

binding = get_option('lib_binding')

subdir('include')
subdir('src')

if binding == 'rust'
  subdir('binding_rust')
elif binding == 'web'
  subdir('binding_web')
endif

library('tree-sitter',
        ts_sources,
        include_directories: ts_include_directories,
        c_args: ['-D_POSIX_C_SOURCE=200112L'],
        install: true)

install_headers(ts_public_headers,
                subdir: 'tree_sitter',
)
