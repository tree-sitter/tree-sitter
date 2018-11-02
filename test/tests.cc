#include "test_helper.h"
#include "helpers/random_helpers.h"

int TREE_SITTER_SEED = 0;

int main(int argc, char *argv[]) {
  const char *seed_env = getenv("TREE_SITTER_SEED");
  if (seed_env) {
    TREE_SITTER_SEED = atoi(seed_env);
  } else {
    TREE_SITTER_SEED = get_time_as_seed();
  }

  printf("Random seed: %d\n", TREE_SITTER_SEED);

  return bandit::run(argc, argv);
}
