#include "runtime/runtime_spec_helper.h"

int main(int argc, char *argv[]) {
  int seed;
  const char *seed_env = getenv("TREE_SITTER_SEED");
  if (seed_env) {
    seed = atoi(seed_env);
  } else {
    seed = time(nullptr);
  }

  printf("Random seed: %d\n", seed);
  srand(seed);

  return bandit::run(argc, argv);
}
