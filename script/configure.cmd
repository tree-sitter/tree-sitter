git submodule update --init --recursive
call .\externals\gyp\gyp.bat project.gyp --depth .
call .\externals\gyp\gyp.bat tests.gyp --depth .
