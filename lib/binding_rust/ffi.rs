#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

include!("./bindings.rs");

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}

use crate::{
    predicate_error, Language, Node, Parser, Query, QueryCursor, QueryError, QueryPredicate,
    QueryPredicateArg, TextPredicate, Tree, TreeCursor,
};
use std::{marker::PhantomData, mem::ManuallyDrop, ptr::NonNull, slice, str};

impl Language {
    /// Reconstructs a [Language] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSLanguage) -> Language {
        Language(ptr)
    }

    /// Consumes the [Language], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *const TSLanguage {
        ManuallyDrop::new(self).0
    }
}

impl Parser {
    /// Reconstructs a [Parser] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSParser) -> Parser {
        Parser(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [Parser], returning a raw pointer to the underlying C structure.
    pub fn into_raw(mut self) -> *mut TSParser {
        self.stop_printing_dot_graphs();
        self.set_logger(None);

        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl Tree {
    /// Reconstructs a [Tree] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSTree) -> Tree {
        Tree(NonNull::new_unchecked(ptr))
    }

    /// Consumes the [Tree], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTree {
        ManuallyDrop::new(self).0.as_ptr()
    }
}

impl<'tree> Node<'tree> {
    /// Reconstructs a [Node] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSNode) -> Node<'tree> {
        Node(*ptr, PhantomData)
    }

    /// Consumes the [Node], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSNode {
        &mut ManuallyDrop::new(self).0
    }
}

impl<'a> TreeCursor<'a> {
    /// Reconstructs a [TreeCursor] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSTreeCursor) -> TreeCursor<'a> {
        TreeCursor(*ptr, PhantomData)
    }

    /// Consumes the [TreeCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSTreeCursor {
        &mut ManuallyDrop::new(self).0
    }
}

impl Query {
    /// Reconstructs a [Query] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSQuery, source: &str) -> Result<Query, QueryError> {
        let string_count = unsafe { ts_query_string_count(ptr) };
        let capture_count = unsafe { ts_query_capture_count(ptr) };
        let pattern_count = unsafe { ts_query_pattern_count(ptr) as usize };
        let mut result = Query {
            ptr: unsafe { NonNull::new_unchecked(ptr) },
            capture_names: Vec::with_capacity(capture_count as usize),
            capture_quantifiers: Vec::with_capacity(pattern_count as usize),
            text_predicates: Vec::with_capacity(pattern_count),
            property_predicates: Vec::with_capacity(pattern_count),
            property_settings: Vec::with_capacity(pattern_count),
            general_predicates: Vec::with_capacity(pattern_count),
        };

        // Build a vector of strings to store the capture names.
        for i in 0..capture_count {
            unsafe {
                let mut length = 0u32;
                let name =
                    ts_query_capture_name_for_id(ptr, i, &mut length as *mut u32) as *const u8;
                let name = slice::from_raw_parts(name, length as usize);
                let name = str::from_utf8_unchecked(name);
                result.capture_names.push(name.to_string());
            }
        }

        // Build a vector to store capture qunatifiers.
        for i in 0..pattern_count {
            let mut capture_quantifiers = Vec::with_capacity(capture_count as usize);
            for j in 0..capture_count {
                unsafe {
                    let quantifier = ts_query_capture_quantifier_for_id(ptr, i as u32, j);
                    capture_quantifiers.push(quantifier.into());
                }
            }
            result.capture_quantifiers.push(capture_quantifiers);
        }

        // Build a vector of strings to represent literal values used in predicates.
        let string_values = (0..string_count)
            .map(|i| unsafe {
                let mut length = 0u32;
                let value = ts_query_string_value_for_id(ptr, i as u32, &mut length as *mut u32)
                    as *const u8;
                let value = slice::from_raw_parts(value, length as usize);
                let value = str::from_utf8_unchecked(value);
                value.to_string()
            })
            .collect::<Vec<_>>();

        // Build a vector of predicates for each pattern.
        for i in 0..pattern_count {
            let predicate_steps = unsafe {
                let mut length = 0u32;
                let raw_predicates =
                    ts_query_predicates_for_pattern(ptr, i as u32, &mut length as *mut u32);
                if length > 0 {
                    slice::from_raw_parts(raw_predicates, length as usize)
                } else {
                    &[]
                }
            };

            let byte_offset = unsafe { ts_query_start_byte_for_pattern(ptr, i as u32) };
            let row = source
                .char_indices()
                .take_while(|(i, _)| *i < byte_offset as usize)
                .filter(|(_, c)| *c == '\n')
                .count();

            let type_done = TSQueryPredicateStepType_TSQueryPredicateStepTypeDone;
            let type_capture = TSQueryPredicateStepType_TSQueryPredicateStepTypeCapture;
            let type_string = TSQueryPredicateStepType_TSQueryPredicateStepTypeString;

            let mut text_predicates = Vec::new();
            let mut property_predicates = Vec::new();
            let mut property_settings = Vec::new();
            let mut general_predicates = Vec::new();
            for p in predicate_steps.split(|s| s.type_ == type_done) {
                if p.is_empty() {
                    continue;
                }

                if p[0].type_ != type_string {
                    return Err(predicate_error(
                        row,
                        format!(
                            "Expected predicate to start with a function name. Got @{}.",
                            result.capture_names[p[0].value_id as usize],
                        ),
                    ));
                }

                // Build a predicate for each of the known predicate function names.
                let operator_name = &string_values[p[0].value_id as usize];
                match operator_name.as_str() {
                    "eq?" | "not-eq?" => {
                        if p.len() != 3 {
                            return Err(predicate_error(
                                row,
                                format!(
                                "Wrong number of arguments to #eq? predicate. Expected 2, got {}.",
                                p.len() - 1
                            ),
                            ));
                        }
                        if p[1].type_ != type_capture {
                            return Err(predicate_error(row, format!(
                                "First argument to #eq? predicate must be a capture name. Got literal \"{}\".",
                                string_values[p[1].value_id as usize],
                            )));
                        }

                        let is_positive = operator_name == "eq?";
                        text_predicates.push(if p[2].type_ == type_capture {
                            TextPredicate::CaptureEqCapture(
                                p[1].value_id,
                                p[2].value_id,
                                is_positive,
                            )
                        } else {
                            TextPredicate::CaptureEqString(
                                p[1].value_id,
                                string_values[p[2].value_id as usize].clone(),
                                is_positive,
                            )
                        });
                    }

                    "match?" | "not-match?" => {
                        if p.len() != 3 {
                            return Err(predicate_error(row, format!(
                                "Wrong number of arguments to #match? predicate. Expected 2, got {}.",
                                p.len() - 1
                            )));
                        }
                        if p[1].type_ != type_capture {
                            return Err(predicate_error(row, format!(
                                "First argument to #match? predicate must be a capture name. Got literal \"{}\".",
                                string_values[p[1].value_id as usize],
                            )));
                        }
                        if p[2].type_ == type_capture {
                            return Err(predicate_error(row, format!(
                                "Second argument to #match? predicate must be a literal. Got capture @{}.",
                                result.capture_names[p[2].value_id as usize],
                            )));
                        }

                        let is_positive = operator_name == "match?";
                        let regex = &string_values[p[2].value_id as usize];
                        text_predicates.push(TextPredicate::CaptureMatchString(
                            p[1].value_id,
                            regex::bytes::Regex::new(regex).map_err(|_| {
                                predicate_error(row, format!("Invalid regex '{}'", regex))
                            })?,
                            is_positive,
                        ));
                    }

                    "set!" => property_settings.push(Self::parse_property(
                        row,
                        &operator_name,
                        &result.capture_names,
                        &string_values,
                        &p[1..],
                    )?),

                    "is?" | "is-not?" => property_predicates.push((
                        Self::parse_property(
                            row,
                            &operator_name,
                            &result.capture_names,
                            &string_values,
                            &p[1..],
                        )?,
                        operator_name == "is?",
                    )),

                    _ => general_predicates.push(QueryPredicate {
                        operator: operator_name.clone().into_boxed_str(),
                        args: p[1..]
                            .iter()
                            .map(|a| {
                                if a.type_ == type_capture {
                                    QueryPredicateArg::Capture(a.value_id)
                                } else {
                                    QueryPredicateArg::String(
                                        string_values[a.value_id as usize].clone().into_boxed_str(),
                                    )
                                }
                            })
                            .collect(),
                    }),
                }
            }

            result
                .text_predicates
                .push(text_predicates.into_boxed_slice());
            result
                .property_predicates
                .push(property_predicates.into_boxed_slice());
            result
                .property_settings
                .push(property_settings.into_boxed_slice());
            result
                .general_predicates
                .push(general_predicates.into_boxed_slice());
        }

        Ok(result)
    }

    /// Consumes the [Query], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQuery {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}

impl QueryCursor {
    /// Reconstructs a [QueryCursor] from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be non-null.
    pub unsafe fn from_raw(ptr: *mut TSQueryCursor) -> QueryCursor {
        QueryCursor {
            ptr: NonNull::new_unchecked(ptr),
        }
    }

    /// Consumes the [QueryCursor], returning a raw pointer to the underlying C structure.
    pub fn into_raw(self) -> *mut TSQueryCursor {
        ManuallyDrop::new(self).ptr.as_ptr()
    }
}
