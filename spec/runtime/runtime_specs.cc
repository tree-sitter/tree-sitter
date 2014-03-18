#include "runtime_spec_helper.h"

int main(int argc, char *argv[]) {
    const char *args[] = {
        "",
        "--no-color",
        "--only="
        "re-reads only"
    };
    return bandit::run(4, const_cast<char **>(args));
}
