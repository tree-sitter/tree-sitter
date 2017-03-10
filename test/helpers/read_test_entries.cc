#include "helpers/read_test_entries.h"
#include <assert.h>
#include <string>
#include <regex>
#include "helpers/file_helpers.h"

using std::regex;
using std::regex_search;
using std::regex_replace;
using std::regex_constants::extended;
using std::smatch;
using std::string;
using std::vector;

string fixtures_dir = "test/fixtures/";

static string trim_output(const string &input) {
  string result(input);
  result = regex_replace(result, regex("[\n\t ]+", extended), string(" "));
  result = regex_replace(result, regex("^ ", extended), string(""));
  result = regex_replace(result, regex(" $", extended), string(""));
  result = regex_replace(result, regex("\\) \\)", extended), string("))"));
  return result;
}

static vector<TestEntry> parse_test_entries(string content) {
  regex header_pattern("===+\n"  "([^=]+)\n"  "===+\n", extended);
  regex separator_pattern("---+\r?\n", extended);
  vector<string> descriptions;
  vector<string> bodies;

  for (;;) {
    smatch matches;
    if (!regex_search(content, matches, header_pattern) || matches.empty())
      break;

    string description = matches[1].str();
    descriptions.push_back(description);

    if (!bodies.empty())
      bodies.back().erase(matches.position());
    content.erase(0, matches.position() + matches[0].length());
    bodies.push_back(content);
  }

  vector<TestEntry> result;
  for (size_t i = 0; i < descriptions.size(); i++) {
    string body = bodies[i];
    smatch matches;
    if (regex_search(body, matches, separator_pattern)) {
      result.push_back({
        descriptions[i],
        body.substr(0, matches.position() - 1),
        trim_output(body.substr(matches.position() + matches[0].length()))
      });
    } else {
      puts(("Invalid corpus entry with description: " + descriptions[i]).c_str());
      abort();
    }
  }

  return result;
}

vector<TestEntry> read_real_language_corpus(string language_name) {
  vector<TestEntry> result;

  string test_directory = fixtures_dir + "grammars/" + language_name + "/grammar_test";
  for (string &test_filename : list_directory(test_directory)) {
    for (TestEntry &entry : parse_test_entries(read_file(test_directory + "/" + test_filename))) {
      result.push_back(entry);
    }
  }

  string error_test_filename = fixtures_dir + "/error_corpus/" + language_name + "_errors.txt";
  for (TestEntry &entry : parse_test_entries(read_file(error_test_filename))) {
    result.push_back(entry);
  }

  return result;
}

vector<TestEntry> read_test_language_corpus(string language_name) {
  vector<TestEntry> result;

  string test_directory = fixtures_dir + "test_grammars/" + language_name;
  for (string &test_filename : list_directory(test_directory)) {
    for (TestEntry &entry : parse_test_entries(read_file(test_directory + "/" + test_filename))) {
      result.push_back(entry);
    }
  }

  return result;
}