use tree_sitter_core::{
    TSInputEncoding, TSLogType, TSQueryError, TSQueryPredicateStepType, TSSymbolType,
};

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}

pub const TSInputEncoding_TSInputEncodingUTF8: TSInputEncoding = 0;
pub const TSInputEncoding_TSInputEncodingUTF16: TSInputEncoding = 1;
#[allow(dead_code)]
pub const TSSymbolType_TSSymbolTypeRegular: TSSymbolType = 0;
#[allow(dead_code)]
pub const TSSymbolType_TSSymbolTypeAnonymous: TSSymbolType = 1;
#[allow(dead_code)]
pub const TSSymbolType_TSSymbolTypeAuxiliary: TSSymbolType = 2;
pub const TSLogType_TSLogTypeParse: TSLogType = 0;
#[allow(dead_code)]
pub const TSLogType_TSLogTypeLex: TSLogType = 1;
pub const TSQueryPredicateStepType_TSQueryPredicateStepTypeDone: TSQueryPredicateStepType = 0;
pub const TSQueryPredicateStepType_TSQueryPredicateStepTypeCapture: TSQueryPredicateStepType = 1;
pub const TSQueryPredicateStepType_TSQueryPredicateStepTypeString: TSQueryPredicateStepType = 2;
#[allow(dead_code)]
pub const TSQueryError_TSQueryErrorNone: TSQueryError = 0;
pub const TSQueryError_TSQueryErrorSyntax: TSQueryError = 1;
pub const TSQueryError_TSQueryErrorNodeType: TSQueryError = 2;
pub const TSQueryError_TSQueryErrorField: TSQueryError = 3;
#[allow(dead_code)]
pub const TSQueryError_TSQueryErrorCapture: TSQueryError = 4;
