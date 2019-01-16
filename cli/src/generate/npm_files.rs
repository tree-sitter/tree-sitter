use std::str;

const BINDING_CC_TEMPLATE: &'static str = include_str!("./templates/binding.cc");
const BINDING_GYP_TEMPLATE: &'static str = include_str!("./templates/binding.gyp");
const INDEX_JS_TEMPLATE: &'static str = include_str!("./templates/index.js");
const PARSER_NAME_PLACEHOLDER: &'static str = "PARSER_NAME";

pub fn binding_cc(parser_name: &str) -> String {
    BINDING_CC_TEMPLATE.replace(PARSER_NAME_PLACEHOLDER, parser_name)
}

pub fn binding_gyp(parser_name: &str) -> String {
    BINDING_GYP_TEMPLATE.replace(PARSER_NAME_PLACEHOLDER, parser_name)
}

pub fn index_js(parser_name: &str) -> String {
    INDEX_JS_TEMPLATE.replace(PARSER_NAME_PLACEHOLDER, parser_name)
}
