use super::*;
use wasmparser::{Validator, WasmFeatures};

const HEADER: &[u8] = b"\0asm\x01\0\0\0";

#[test]
fn adds_maximum_and_preserves_other_sections() {
    let wasm = module(&[0, 1], &[0], &[1, b'x']);
    let converted = with_compatible_memory_import(&wasm, Some(130), true).unwrap();
    let expected = module(&[3, 1, 130, 1], &[0], &[1, b'x']);
    assert_eq!(converted.as_ref(), expected);
    assert!(matches!(converted, Cow::Owned(_)));
    Validator::new_with_features(WasmFeatures::default())
        .validate_all(converted.as_ref())
        .unwrap();
}

#[test]
fn flips_only_flags_when_maximum_exists() {
    let wasm = module(&[1, 2, 10], &[0], &[1, b'x']);
    let converted = with_compatible_memory_import(&wasm, Some(8), true).unwrap();
    assert_eq!(converted.as_ref(), module(&[3, 2, 10], &[0], &[1, b'x']));
    assert_eq!(converted.len(), wasm.len());
}

#[test]
fn already_shared_is_borrowed() {
    let wasm = module(&[3, 1, 10], &[], &[]);
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Ok(Cow::Borrowed(_))
    ));
}

#[test]
fn unshared_host_keeps_matching_imports_and_rejects_shared_ones() {
    let unbounded = module(&[0, 1], &[], &[]);
    assert!(matches!(
        with_compatible_memory_import(&unbounded, None, false),
        Ok(Cow::Borrowed(_))
    ));
    let bounded = module(&[1, 1, 10], &[], &[]);
    assert!(matches!(
        with_compatible_memory_import(&bounded, Some(8), false),
        Ok(Cow::Borrowed(_))
    ));
    assert!(matches!(
        with_compatible_memory_import(&bounded, None, false),
        Err(MemoryImportError::IncompatibleLimits)
    ));
    assert!(matches!(
        with_compatible_memory_import(&module(&[3, 1, 10], &[], &[]), Some(8), false),
        Err(MemoryImportError::UnsupportedMemory)
    ));
    assert!(matches!(
        with_compatible_memory_import(&unbounded, None, true),
        Err(MemoryImportError::IncompatibleLimits)
    ));
}

#[test]
fn rejects_missing_duplicate_and_other_memory_imports() {
    assert!(matches!(
        with_compatible_memory_import(HEADER, Some(10), true),
        Err(MemoryImportError::MissingMemory)
    ));
    let mut wasm = HEADER.to_vec();
    let entry = import("env", "memory", &[0, 1]);
    let mut imports = vec![2];
    imports.extend_from_slice(&entry);
    imports.extend_from_slice(&entry);
    section(2, &imports, &mut wasm);
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Err(MemoryImportError::DuplicateMemory)
    ));
    let mut wasm = HEADER.to_vec();
    section(
        2,
        &[
            1, 3, b'f', b'o', b'o', 6, b'm', b'e', b'm', b'o', b'r', b'y', 2, 0, 1,
        ],
        &mut wasm,
    );
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Err(MemoryImportError::UnsupportedMemory)
    ));
}

#[test]
fn rejects_memory64_and_incompatible_limits() {
    let wasm = module(&[4, 1], &[], &[]);
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Err(MemoryImportError::UnsupportedMemory)
    ));
    assert!(matches!(
        with_compatible_memory_import(&module(&[2, 1], &[], &[]), Some(10), true),
        Err(MemoryImportError::IncompatibleLimits)
    ));
    for limits in [&[0, 11][..], &[1, 1, 9], &[3, 1, 9]] {
        assert!(matches!(
            with_compatible_memory_import(&module(limits, &[], &[]), Some(10), true),
            Err(MemoryImportError::IncompatibleLimits)
        ));
    }
}

#[test]
fn rejects_truncated_import_and_bad_section_size() {
    let mut wasm = module(&[0, 1], &[], &[]);
    wasm.pop();
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Err(MemoryImportError::InvalidWasm(_))
    ));
    let mut wasm = module(&[0, 1], &[], &[]);
    wasm[9] = 0x7f;
    assert!(matches!(
        with_compatible_memory_import(&wasm, Some(10), true),
        Err(MemoryImportError::InvalidWasm(_))
    ));
}

#[test]
fn grows_multibyte_section_length_without_changing_other_sections() {
    let mut wasm = HEADER.to_vec();
    section(1, &[1, 0x60, 0, 0], &mut wasm);
    let long_name = "a".repeat(104);
    let mut imports = vec![2];
    imports.extend_from_slice(&import("env", "memory", &[0, 1]));
    encode_u32(3, &mut imports);
    imports.extend_from_slice(b"env");
    encode_u32(long_name.len() as u32, &mut imports);
    imports.extend_from_slice(long_name.as_bytes());
    imports.extend_from_slice(&[0, 0]);
    section(2, &imports, &mut wasm);
    let converted = with_compatible_memory_import(&wasm, Some(200), true).unwrap();
    assert_eq!(wasm[15], 126);
    assert_eq!(&converted[15..17], &[128, 1]);
    Validator::new_with_features(WasmFeatures::default())
        .validate_all(converted.as_ref())
        .unwrap();
}

fn module(limits: &[u8], type_section: &[u8], custom_section: &[u8]) -> Vec<u8> {
    let mut wasm = HEADER.to_vec();
    if !custom_section.is_empty() {
        section(0, custom_section, &mut wasm);
    }
    if !type_section.is_empty() {
        section(1, type_section, &mut wasm);
    }
    let mut imports = vec![1];
    imports.extend_from_slice(&import("env", "memory", limits));
    section(2, &imports, &mut wasm);
    wasm
}

fn import(module: &str, name: &str, limits: &[u8]) -> Vec<u8> {
    let mut entry = Vec::new();
    encode_u32(module.len() as u32, &mut entry);
    entry.extend_from_slice(module.as_bytes());
    encode_u32(name.len() as u32, &mut entry);
    entry.extend_from_slice(name.as_bytes());
    entry.push(2);
    entry.extend_from_slice(limits);
    entry
}

fn section(id: u8, contents: &[u8], wasm: &mut Vec<u8>) {
    wasm.push(id);
    encode_u32(contents.len() as u32, wasm);
    wasm.extend_from_slice(contents);
}
