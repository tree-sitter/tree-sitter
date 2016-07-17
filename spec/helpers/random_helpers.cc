#include <string>
#include <stdlib.h>

using std::string;

static string random_string(char min, char max) {
  string result;
  size_t length = random() % 12;
  for (size_t i = 0; i < length; i++) {
    char inserted_char = min + (random() % (max - min));
    result += inserted_char;
  }
  return result;
}

static string random_char(string characters) {
  size_t index = random() % characters.size();
  return string() + characters[index];
}

string random_words(size_t count) {
  string result;
  bool just_inserted_word = false;
  for (size_t i = 0; i < count; i++) {
    if (random() % 10 < 6) {
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
