#include "test_helper.h"
#include "helpers/random_helpers.h"

int main(int argc, char *argv[]) {
  int seed;
  const char *seed_env = getenv("TREE_SITTER_SEED");
  if (seed_env) {
    seed = atoi(seed_env);
  } else {
    seed = get_time_as_seed();
  }

  printf("Random seed: %d\n", seed);
  random_reseed(seed);

  return bandit::run(argc, argv);
}
