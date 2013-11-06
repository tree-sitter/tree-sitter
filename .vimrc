set wildignore+=spec/externals
set wildignore+=TreeSitter.xcodeproj/*
set shiftwidth=4
set softtabstop=4
set tabstop=4

let g:syntastic_cpp_compiler = 'clang'
let g:syntastic_cpp_auto_refresh_includes = 1
let g:syntastic_cpp_include_dirs = [ './core/include', './spec/externals/igloo', './spec', './src' ]
let g:syntastic_cpp_compiler_options = '-std=gnu99 -fnested-functions -DRUBY_MISSING_H'
