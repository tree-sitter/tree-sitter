#include "helpers/read_test_entries.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <dirent.h>

#ifdef USE_BOOST_REGEX

#include "boost/regex.hpp"
using boost::regex;
using boost::regex_search;
using boost::regex_replace;
using boost::smatch;
using boost::regex_constants::extended;

#else

#include <regex>
using std::regex;
using std::regex_search;
using std::regex_replace;
using std::smatch;
using std::regex_constants::extended;

#endif

using std::string;
using std::vector;
using std::ifstream;
using std::istreambuf_iterator;

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
  regex separator_pattern("---+", extended);
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
          body.substr(0, matches.position()),
          trim_output(body.substr(matches.position() + matches[0].length()))
      });
    }
  }

	return result;
}

static vector<string> list_directory(string dir_name) {
	vector<string> result;

	DIR *dir = opendir(dir_name.c_str());
	if (!dir) {
    printf("\nTest error - no such directory '%s'", dir_name.c_str());
    return result;
  }

	struct dirent *dir_entry;
	while ((dir_entry = readdir(dir))) {
		string name(dir_entry->d_name);
		if (name != "." && name != "..")
			result.push_back(dir_name + "/" + name);
	}

  closedir(dir);
	return result;
}

static string read_file(string filename) {
  ifstream file(filename);
  string result((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
  return result;
}

vector<TestEntry> read_corpus_entries(string language_name) {
  vector<TestEntry> result;

  string fixtures_dir = "spec/fixtures/";

  string test_directory = fixtures_dir + "grammars/" + language_name + "/grammar_test";
  for (string &test_filename : list_directory(test_directory))
    for (TestEntry &entry : parse_test_entries(read_file(test_filename)))
      result.push_back(entry);

  string error_test_filename = fixtures_dir + "/error_corpus/" + language_name + "_errors.txt";
  for (TestEntry &entry : parse_test_entries(read_file(error_test_filename)))
    result.push_back(entry);

  return result;
}
