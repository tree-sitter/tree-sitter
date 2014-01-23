#include "parse_config.h"
#include <string>

using std::string;
static const char * EMPTY = "";

const char * TSParseErrorToString(const TSParseError *error, const char *input_string, const char **symbol_names) {
    string result;
    switch (error->type) {
        case TSParseErrorTypeSyntactic:
            result = string("Unexpected token ") + symbol_names[error->lookahead_sym] + ". ";
            break;
        case TSParseErrorTypeLexical:
            result = string("Unexpected character '") + (input_string + error->position) + "'. ";
            break;
        default:
            return EMPTY;
    }
    
    result += "Expected: ";
    for (int i = 0; i < error->expected_input_count; i++)
        result += string(error->expected_inputs[i]) + " ";

    char *stuff = (char *)malloc(result.size() * sizeof(char));
    strcpy(stuff, result.c_str());
    return stuff;
}
