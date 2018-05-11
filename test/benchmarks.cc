#include <cassert>
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include "tree_sitter/runtime.h"
#include "helpers/load_language.h"
#include "helpers/stderr_logger.h"
#include "helpers/read_test_entries.h"

using std::map;
using std::vector;
using std::string;

vector<string> language_names({
  "c",
  "cpp",
  "javascript",
  "python",
  "bash",
});

size_t mean(const vector<size_t> &values) {
  if (values.empty()) return 0;
  size_t result = 0;
  for (size_t value : values) {
    result += value;
  }
  return result / values.size();
}

size_t min(const vector<size_t> &values) {
  size_t result = 0;
  for (unsigned i = 0; i < values.size(); i++) {
    size_t value = values[i];
    if (i == 0 || value < result) result = value;
  }
  return result;
}

int main(int argc, char *arg[]) {
  map<string, vector<ExampleEntry>> example_entries_by_language_name;
  vector<size_t> error_speeds;
  vector<size_t> non_error_speeds;

  TSParser *parser = ts_parser_new();

  if (getenv("TREE_SITTER_BENCHMARK_SVG")) {
    ts_parser_print_dot_graphs(parser, stderr);
  } else if (getenv("TREE_SITTER_BENCHMARK_LOG")) {
    ts_parser_set_logger(parser, stderr_logger_new(false));
  }

  auto language_filter = getenv("TREE_SITTER_BENCHMARK_LANGUAGE");
  auto file_name_filter = getenv("TREE_SITTER_BENCHMARK_FILE_NAME");

  for (auto &language_name : language_names) {
    example_entries_by_language_name[language_name] = examples_for_language(language_name);
  }

  for (auto &language_name : language_names) {
    if (language_filter && language_name != language_filter) continue;

    ts_parser_set_language(parser, load_real_language(language_name));

    printf("%s\n", language_name.c_str());

    for (auto &example : example_entries_by_language_name[language_name]) {
      if (file_name_filter && example.file_name != file_name_filter) continue;
      if (example.input.size() < 256) continue;

      clock_t start_time = clock();
      TSTree *tree = ts_parser_parse_string(parser, nullptr, example.input.c_str(), example.input.size());
      clock_t end_time = clock();

      assert(!ts_node_has_error(ts_tree_root_node(tree)));
      ts_tree_delete(tree);

      size_t duration = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
      size_t speed = static_cast<double>(example.input.size()) / duration;
      printf("  %-30s\t%lu ms\t\t%lu bytes/ms\n", example.file_name.c_str(), duration, speed);
      if (speed != 0) non_error_speeds.push_back(speed);
    }

    for (auto &other_language_name : language_names) {
      if (other_language_name == language_name) continue;

      for (auto &example : example_entries_by_language_name[other_language_name]) {
        if (file_name_filter && example.file_name != file_name_filter) continue;
        if (example.input.size() < 256) continue;

        clock_t start_time = clock();
        TSTree *tree = ts_parser_parse_string(parser, nullptr, example.input.c_str(), example.input.size());
        clock_t end_time = clock();

        ts_tree_delete(tree);

        size_t duration = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
        size_t speed = static_cast<double>(example.input.size()) / duration;
        printf("  %-30s\t%lu ms\t\t%lu bytes/ms\n", example.file_name.c_str(), duration, speed);
        if (speed != 0) error_speeds.push_back(speed);
      }
    }

    puts("");
  }

  puts("without errors:");
  printf("  %-30s\t%lu bytes/ms\n", "average speed", mean(non_error_speeds));
  printf("  %-30s\t%lu bytes/ms\n", "worst speed", min(non_error_speeds));
  puts("");

  puts("with errors:");
  printf("  %-30s\t%lu bytes/ms\n", "average speed", mean(error_speeds));
  printf("  %-30s\t%lu bytes/ms\n", "worst speed", min(error_speeds));

  ts_parser_delete(parser);
  return 0;
}
