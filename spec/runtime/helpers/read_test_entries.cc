#include "helpers/read_test_entries.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>
#include <dirent.h>

using std::string;
using std::vector;
using std::ifstream;
using std::istreambuf_iterator;
using std::regex;
using std::regex_search;
using std::regex_replace;

static string trim_output(const string &input) {
    string result(input);
    result = regex_replace(result, regex("^[\\s]+"), "");
    result = regex_replace(result, regex("[\\s]+$"), "");
    result = regex_replace(result, regex("\\)\\s+\\)"), "))");
    result = regex_replace(result, regex("\\s+"), " ");
    return result;
}

static vector<TestEntry> get_test_entries_from_string(string content) {
    regex header_pattern("===+\n"  "([^=]+)\n"  "===+\n");
    regex separator_pattern("---+");

    vector<string> descriptions;
    vector<string> bodies;

    for (;;) {
        std::smatch matches;
        regex_search(content, matches, header_pattern);
        if (matches.empty()) break;

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
        std::smatch matches;
        regex_search(body, matches, separator_pattern);
        result.push_back({
            .description = descriptions[i],
            .input = body.substr(0, matches.position()),
            .tree_string = trim_output(body.substr(matches.position() + matches[0].length()))
        });
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
	return result;
}

static string src_dir() {
    const char *dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}

vector<TestEntry> test_entries_for_language(string language) {
    vector<TestEntry> result;
    string language_dir = src_dir() + "/spec/runtime/languages/" + language;
    vector<string> filenames = list_directory(language_dir);

    for (string &filename : filenames) {
        ifstream file(filename);
        std::string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        for (TestEntry &entry : get_test_entries_from_string(content))
            result.push_back(entry);
    }

    return result;
}
