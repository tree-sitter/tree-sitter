#ifndef HELPERS_RANDOM_HELPERS_H_
#define HELPERS_RANDOM_HELPERS_H_

#include <string>
#include <vector>
#include <random>

unsigned get_time_as_seed();

class Generator {
  std::default_random_engine engine;
  std::uniform_int_distribution<uint32_t> distribution;

public:
  Generator(uint32_t seed) : engine{seed} {}

  void reseed(unsigned);
  unsigned operator()();
  unsigned operator()(unsigned max);
  std::string words(size_t count);
  std::string str(char min, char max);
  std::string select(const std::vector<std::string> &);
  void sleep_some();
};

extern Generator default_generator;

#endif  // HELPERS_RANDOM_HELPERS_H_
