#include "tree_sitter/runtime.h"
#include <string>
#include "string.h"

using std::string;

const char * ts_error_string(const ts_error *error, const char *input_string, const char **symbol_names) {
    string result = string("Unexpected character '") + input_string[error->position] + "'. Expected: ";
    for (int i = 0; i < error->expected_input_count; i++)
        result += string(error->expected_inputs[i]) + " ";

    char *stuff = (char *)malloc(result.size() * sizeof(char));
    strcpy(stuff, result.c_str());
    return stuff;
}
