#include <napi.h>

typedef struct TSLanguage TSLanguage;

extern "C" TSLanguage *tree_sitter_PARSER_NAME();

// tstag() {
//   b2sum -l64 <(printf tree-sitter) <(printf "$1") | \
//   awk '{printf "0x" toupper($1) (NR == 1 ? ", " : "\n")}'
// }
// tstag language # => 0x8AF2E5212AD58ABF, 0xD5006CAD83ABBA16
const napi_type_tag LANGUAGE_TYPE_TAG = {
  0x8AF2E5212AD58ABF, 0xD5006CAD83ABBA16
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports["name"] = Napi::String::New(env, "PARSER_NAME");
    auto language = Napi::External<TSLanguage>::New(env, tree_sitter_PARSER_NAME());
    language.TypeTag(&LANGUAGE_TYPE_TAG);
    exports["language"] = language;
    return exports;
}

NODE_API_MODULE(tree_sitter_PARSER_NAME_binding, Init)
