#include <string>
#include <vector>
#include <random>
#include <time.h>

using std::string;
using std::vector;

static std::default_random_engine engine;

unsigned get_time_as_seed() {
  return time(nullptr);
}

void random_reseed(unsigned seed) {
  engine.seed(seed);
}

unsigned random_unsigned() {
  return std::uniform_int_distribution<unsigned>()(engine);
}

unsigned random_unsigned(unsigned max) {
  return std::uniform_int_distribution<unsigned>(0, max - 1)(engine);
}

static string random_string(char min, char max) {
  string result;
  size_t length = random_unsigned(12);
  for (size_t i = 0; i < length; i++) {
    result += (min + random_unsigned(max - min));
  }
  return result;
}

static string random_char(string characters) {
  size_t index = random_unsigned(characters.size());
  return string() + characters[index];
}

string random_words(size_t count) {
  string result;
  bool just_inserted_word = false;
  for (size_t i = 0; i < count; i++) {
    if (random_unsigned(10) < 6) {
      result += random_char("!(){}[]<>+-=");
    } else {
      if (just_inserted_word)
        result += " ";
      result += random_string('a', 'z');
      just_inserted_word = true;
    }
  }
  return result;
}

string select_random(const vector<string> &list) {
  return list[random_unsigned(list.size())];
}
