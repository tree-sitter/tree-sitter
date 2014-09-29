import os
import ycm_core
from clang_helpers import PrepareClangFlags


cxx_flags = [
    '-Wall',
    '-std=c++11',
    '-stdlib=libc++',
    '-x', 'c++',
    '-I', '.',
    '-I', 'src',
    '-I', 'spec',
    '-I', 'include',
    '-I', 'externals/bandit',
    '-I', 'externals/utf8proc',
    '-isystem', '/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/c++/v1',
]


c_flags = [
    '-Wall',
    '-std=c99',
    '-I', '.',
    '-I', 'src',
    '-I', 'spec',
    '-I', 'include',
    '-I', 'externals/bandit',
    '-I', 'externals/utf8proc',
    '-isystem',
    '/usr/lib/c++/v1'
]


def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def MakeRelativePathsInFlagsAbsolute(flags, working_directory):
    if not working_directory:
        return flags
    new_flags = []
    make_next_absolute = False
    path_flags = ['-isystem', '-I', '-iquote', '--sysroot=']
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith('/'):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith(path_flag):
                path = flag[len(path_flag):]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append(new_flag)
    return new_flags


def IsPlainCFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension == '.c'


def FlagsForFile(filename):
    flags = None

    if IsPlainCFile(filename):
        flags = c_flags
    else:
        flags = cxx_flags

    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute(flags, relative_to)

    return {
        'flags': final_flags,
        'do_cache': True}
