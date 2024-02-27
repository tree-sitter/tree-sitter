#include <napi.h>

typedef struct TSLanguage TSLanguage;

extern "C" TSLanguage *tree_sitter_PARSER_NAME();

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports["name"] = Napi::String::New(env, "PARSER_NAME");
    exports["language"] = Napi::External<TSLanguage>::New(env, tree_sitter_PARSER_NAME());
    return exports;
}

NODE_API_MODULE(tree_sitter_PARSER_NAME_binding, Init)
