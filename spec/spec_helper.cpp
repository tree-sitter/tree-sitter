#include "spec_helper.h"

string src_dir() {
    const char * dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}