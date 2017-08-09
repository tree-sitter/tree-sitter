#ifndef HELPERS_RANDOM_HELPERS_H_
#define HELPERS_RANDOM_HELPERS_H_

#include <string>
#include <vector>

unsigned get_time_as_seed();
void random_reseed(unsigned);
unsigned random_unsigned();
unsigned random_unsigned(unsigned max);
std::string random_words(size_t count);
std::string select_random(const std::vector<std::string> &);

#endif  // HELPERS_RANDOM_HELPERS_H_
