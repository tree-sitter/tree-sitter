ts_public_headers = []
ts_sources = []

ts_include_directories = []

subdir('include')
subdir('src')

library('tree-sitter',
        ts_sources,
        include_directories: ts_include_directories,
        c_args: ['-D_POSIX_C_SOURCE=200112L'],
        install: true)

install_headers(ts_public_headers,
                subdir: 'tree_sitter',
)
