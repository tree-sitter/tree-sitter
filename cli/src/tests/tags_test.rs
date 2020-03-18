use super::helpers::allocations;
use super::helpers::fixtures::get_language;
use std::ffi::CString;
use std::{ptr, slice, str};
use tree_sitter_tags::c_lib as c;
use tree_sitter_tags::{TagKind, TagsConfiguration, TagsContext};

const PYTHON_TAG_QUERY: &'static str = r#"
((function_definition
  name: (identifier) @name
  body: (block . (expression_statement (string) @doc))) @function
 (strip! @doc "(^['\"\\s]*)|(['\"\\s]*$)"))
(function_definition
  name: (identifier) @name) @function
((class_definition
  name: (identifier) @name
  body: (block . (expression_statement (string) @doc))) @class
 (strip! @doc "(^['\"\\s]*)|(['\"\\s]*$)"))
(class_definition
  name: (identifier) @name) @class
(call
  function: (identifier) @name) @call
"#;

const JS_TAG_QUERY: &'static str = r#"
((*
    (comment)+ @doc .
    (class_declaration
        name: (identifier) @name) @class)
 (select-adjacent! @doc @class)
 (strip! @doc "(^[/\\*\\s]*)|([/\\*\\s]*$)"))

((*
    (comment)+ @doc .
    (method_definition
        name: (property_identifier) @name) @method)
 (select-adjacent! @doc @method)
 (strip! @doc "(^[/\\*\\s]*)|([/\\*\\s]*$)"))

((*
    (comment)+ @doc .
    (function_declaration
        name: (identifier) @name) @function)
 (select-adjacent! @doc @function)
 (strip! @doc "(^[/\\*\\s]*)|([/\\*\\s]*$)"))

(call_expression function: (identifier) @name) @call
  "#;

#[test]
fn test_tags_python() {
    let language = get_language("python");
    let tags_config = TagsConfiguration::new(language, PYTHON_TAG_QUERY, "").unwrap();

    let source = br#"
    class Customer:
        """
        Data about a customer
        """

        def age(self):
            '''
            Get the customer's age
            '''
            compute_age(self.id)
    }
    "#;

    let mut tag_context = TagsContext::new();
    let tags = tag_context
        .generate_tags(&tags_config, source)
        .collect::<Vec<_>>();

    assert_eq!(
        tags.iter()
            .map(|t| (substr(source, &t.name_range), t.kind))
            .collect::<Vec<_>>(),
        &[
            ("Customer", TagKind::Class),
            ("age", TagKind::Function),
            ("compute_age", TagKind::Call),
        ]
    );

    assert_eq!(substr(source, &tags[0].line_range), "    class Customer:");
    assert_eq!(
        substr(source, &tags[1].line_range),
        "        def age(self):"
    );
    assert_eq!(tags[0].docs.as_ref().unwrap(), "Data about a customer");
    assert_eq!(tags[1].docs.as_ref().unwrap(), "Get the customer's age");
}

#[test]
fn test_tags_javascript() {
    let language = get_language("javascript");
    let tags_config = TagsConfiguration::new(language, JS_TAG_QUERY, "").unwrap();

    let mut tag_context = TagsContext::new();
    let source = br#"
    // hi

    // Data about a customer.
    // bla bla bla
    class Customer {
        /*
         * Get the customer's age
         */
        getAge() {
        }
    }

    // ok

    class Agent {

    }
    "#;
    let tags = tag_context
        .generate_tags(&tags_config, source)
        .collect::<Vec<_>>();

    assert_eq!(
        tags.iter()
            .map(|t| (substr(source, &t.name_range), t.kind))
            .collect::<Vec<_>>(),
        &[
            ("getAge", TagKind::Method),
            ("Customer", TagKind::Class),
            ("Agent", TagKind::Class)
        ]
    );
    assert_eq!(tags[0].docs.as_ref().unwrap(), "Get the customer's age");
    assert_eq!(
        tags[1].docs.as_ref().unwrap(),
        "Data about a customer.\nbla bla bla"
    );
    assert_eq!(tags[2].docs, None);
}

#[test]
fn test_tags_via_c_api() {
    allocations::record(|| {
        let tagger = c::ts_tagger_new();
        let buffer = c::ts_tags_buffer_new();
        let scope_name = "source.js";
        let language = get_language("javascript");

        let source_code = "
            var a = 1;

            // one
            // two
            // three
            function b() {
            }

            // four
            // five
            class C extends D {

            }

            b(a);"
            .lines()
            .skip(1)
            // remove extra indentation
            .map(|line| &line[line.len().min(12)..])
            .collect::<Vec<_>>()
            .join("\n");

        let c_scope_name = CString::new(scope_name).unwrap();
        let result = c::ts_tagger_add_language(
            tagger,
            c_scope_name.as_ptr(),
            language,
            JS_TAG_QUERY.as_ptr(),
            ptr::null(),
            JS_TAG_QUERY.len() as u32,
            0,
        );
        assert_eq!(result, c::TSTagsError::Ok);

        let result = c::ts_tagger_tag(
            tagger,
            c_scope_name.as_ptr(),
            source_code.as_ptr(),
            source_code.len() as u32,
            buffer,
            ptr::null(),
        );
        assert_eq!(result, c::TSTagsError::Ok);
        let tags = unsafe {
            slice::from_raw_parts(
                c::ts_tags_buffer_tags(buffer),
                c::ts_tags_buffer_tags_len(buffer) as usize,
            )
        };
        let docs = str::from_utf8(unsafe {
            slice::from_raw_parts(
                c::ts_tags_buffer_docs(buffer) as *const u8,
                c::ts_tags_buffer_docs_len(buffer) as usize,
            )
        })
        .unwrap();

        assert_eq!(
            tags.iter()
                .map(|tag| (
                    tag.kind,
                    &source_code[tag.name_start_byte as usize..tag.name_end_byte as usize],
                    &source_code[tag.line_start_byte as usize..tag.line_end_byte as usize],
                    &docs[tag.docs_start_byte as usize..tag.docs_end_byte as usize],
                ))
                .collect::<Vec<_>>(),
            &[
                (
                    c::TSTagKind::Function,
                    "b",
                    "function b() {",
                    "one\ntwo\nthree"
                ),
                (
                    c::TSTagKind::Class,
                    "C",
                    "class C extends D {",
                    "four\nfive"
                ),
                (c::TSTagKind::Call, "b", "b(a);", "")
            ]
        );

        c::ts_tags_buffer_delete(buffer);
        c::ts_tagger_delete(tagger);
    });
}

fn substr<'a>(source: &'a [u8], range: &std::ops::Range<usize>) -> &'a str {
    std::str::from_utf8(&source[range.clone()]).unwrap()
}
