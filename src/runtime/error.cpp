#include "tree_sitter/runtime.h"
#include <string>

using std::string;

const char * TSParseErrorToString(const TSParseError *error, const char *input_string, const char **symbol_names) {
    string result = string("Unexpected character '") + input_string[error->position] + "'. Expected: ";
    for (int i = 0; i < error->expected_input_count; i++)
        result += string(error->expected_inputs[i]) + " ";

    char *stuff = (char *)malloc(result.size() * sizeof(char));
    strcpy(stuff, result.c_str());
    return stuff;
}
