#include "nan.h"
#include <node.h>

using namespace v8;

typedef struct TSLanguage TSLanguage;

extern "C" const TSLanguage *tree_sitter_PARSER_NAME(void);

namespace {

NAN_METHOD(New) {}

void Init(Local<Object> exports, Local<Object> module) {
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Language").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Local<Function> constructor = Nan::GetFunction(tpl).ToLocalChecked();
    Local<Object> instance = constructor->NewInstance(Nan::GetCurrentContext()).ToLocalChecked();
    Nan::SetInternalFieldPointer(instance, 0, (void *)tree_sitter_PARSER_NAME());

    Nan::Set(instance, Nan::New("name").ToLocalChecked(), Nan::New("PARSER_NAME").ToLocalChecked());
    Nan::Set(module, Nan::New("exports").ToLocalChecked(), instance);
}

NODE_MODULE_CONTEXT_AWARE(tree_sitter_PARSER_NAME_binding, Init)

} // namespace
