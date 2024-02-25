#include "tree_sitter/parser.h"
#include <napi.h>

using namespace Napi;

extern "C" TSLanguage * tree_sitter_PARSER_NAME();

namespace {

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["name"] = String::New(env, "PARSER_NAME");
  exports["language"] = External<TSLanguage>::New(env, tree_sitter_PARSER_NAME());
  return exports;
}

NODE_API_MODULE(tree_sitter_PARSER_NAME_binding, Init)

}  // namespace
