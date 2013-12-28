#include "spec_helper.h"

int main(int argc, char *argv[])
{
    char *args[] = {nullptr, (char *)"--no-color"};
    return bandit::run(2, args);
}