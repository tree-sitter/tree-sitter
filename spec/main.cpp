#include "spec_helper.h"

int main(int argc, char *argv[])
{
    const char *args[] = {
        "",
        "--no-color",
        "--only="
        "parenthesized expr"
    };
    return bandit::run(4, const_cast<char **>(args));
}