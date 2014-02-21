#include "tree_sitter/runtime.h"
#include <string>
#include "string.h"

using std::string;

const char * ts_error_string(const ts_error *error) {
    string result = string("Unexpected character '") + error->lookahead_char + "'. Expected:";
    for (int i = 0; i < error->expected_input_count; i++) {
        result += string(" ") + error->expected_inputs[i];
    }

    char *stuff = (char *)malloc(result.size() * sizeof(char));
    strcpy(stuff, result.c_str());
    return stuff;
}
