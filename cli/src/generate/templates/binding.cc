#include "tree_sitter/parser.h"
#include <napi.h>

extern "C" TSLanguage * tree_sitter_PARSER_NAME();

namespace {

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["name"] = Napi::String::New(env, "PARSER_NAME");
  exports["language"] = Napi::External<TSLanguage>::New(env, tree_sitter_PARSER_NAME());
  return exports;
}

}  // namespace

NODE_API_MODULE(tree_sitter_PARSER_NAME_binding, Init)
