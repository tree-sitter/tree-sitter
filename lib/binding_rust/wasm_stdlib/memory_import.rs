use std::{borrow::Cow, fmt};

use wasmparser::{BinaryReader, Imports, Parser, Payload, TypeRef};

/// Why an imported memory cannot be used with the loader's shared host memory.
#[derive(Debug)]
pub enum MemoryImportError {
    InvalidWasm(wasmparser::BinaryReaderError),
    MissingMemory,
    DuplicateMemory,
    UnsupportedMemory,
    IncompatibleLimits,
}

impl fmt::Display for MemoryImportError {
    fn fmt(&self, formatter: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::InvalidWasm(error) => write!(formatter, "invalid Wasm module: {error}"),
            Self::MissingMemory => write!(formatter, "missing env.memory import"),
            Self::DuplicateMemory => write!(formatter, "multiple memory imports"),
            Self::UnsupportedMemory => write!(formatter, "unsupported memory import"),
            Self::IncompatibleLimits => write!(formatter, "incompatible memory limits"),
        }
    }
}

impl std::error::Error for MemoryImportError {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        match self {
            Self::InvalidWasm(error) => Some(error),
            _ => None,
        }
    }
}

impl From<wasmparser::BinaryReaderError> for MemoryImportError {
    fn from(error: wasmparser::BinaryReaderError) -> Self {
        Self::InvalidWasm(error)
    }
}

/// Makes a module's `env.memory` import compatible with the host memory.
///
/// Other sections, including custom sections, retain their exact original bytes.
/// `host_max_pages` is `None` only for an unshared host without a declared
/// maximum. The caller must also supply memory with a sufficient minimum.
pub fn with_compatible_memory_import(
    bytes: &[u8],
    host_max_pages: Option<u32>,
    host_shared: bool,
) -> Result<Cow<'_, [u8]>, MemoryImportError> {
    let mut memory = None;
    for payload in Parser::new(0).parse_all(bytes) {
        if let Payload::ImportSection(section) = payload? {
            let section_range = section.range();
            for group in section {
                let Imports::Single(offset, import) = group? else {
                    return Err(MemoryImportError::UnsupportedMemory);
                };
                if let TypeRef::Memory(memory_type) = import.ty {
                    if memory.is_some() {
                        return Err(MemoryImportError::DuplicateMemory);
                    }
                    if import.module != "env" || import.name != "memory" {
                        return Err(MemoryImportError::UnsupportedMemory);
                    }
                    memory = Some((offset, section_range.clone(), memory_type));
                } else if import.module == "env" && import.name == "memory" {
                    return Err(MemoryImportError::UnsupportedMemory);
                }
            }
        }
    }

    let (offset, section_range, memory_type) = memory.ok_or(MemoryImportError::MissingMemory)?;
    if memory_type.memory64 || memory_type.page_size_log2.is_some() {
        return Err(MemoryImportError::UnsupportedMemory);
    }
    if memory_type
        .maximum
        .is_some_and(|maximum| maximum < memory_type.initial)
        || (memory_type.shared && memory_type.maximum.is_none())
    {
        return Err(MemoryImportError::IncompatibleLimits);
    }
    match host_max_pages {
        Some(maximum) if maximum <= 65_536 => {
            if memory_type.initial > u64::from(maximum)
                || memory_type
                    .maximum
                    .is_some_and(|import_maximum| import_maximum < u64::from(maximum))
            {
                return Err(MemoryImportError::IncompatibleLimits);
            }
        }
        None if !host_shared && memory_type.maximum.is_none() => {}
        Some(_) | None => return Err(MemoryImportError::IncompatibleLimits),
    }
    if !host_shared {
        if memory_type.shared {
            return Err(MemoryImportError::UnsupportedMemory);
        }
        return Ok(Cow::Borrowed(bytes));
    }
    if memory_type.shared {
        return Ok(Cow::Borrowed(bytes));
    }
    let host_max_pages = host_max_pages.ok_or(MemoryImportError::IncompatibleLimits)?;

    // wasmparser identified a plain 32-bit memory import. Read just its header
    // to locate the limits, leaving every other import untouched.
    let mut reader = BinaryReader::new(&bytes[offset..section_range.end], offset);
    reader.read_string()?;
    reader.read_string()?;
    if reader.read_u8()? != 2 {
        return Err(MemoryImportError::UnsupportedMemory);
    }
    let flags_offset = reader.original_position();
    let flags = reader.read_u8()?;
    if flags != u8::from(memory_type.maximum.is_some()) {
        return Err(MemoryImportError::UnsupportedMemory);
    }
    reader.read_var_u32()?;
    let minimum_end = reader.original_position();

    if memory_type.maximum.is_some() {
        let mut converted = bytes.to_vec();
        converted[flags_offset] = 3;
        return Ok(Cow::Owned(converted));
    }

    let mut maximum = Vec::new();
    encode_u32(host_max_pages, &mut maximum);
    let section_length = section_range
        .len()
        .checked_add(maximum.len())
        .and_then(|length| u32::try_from(length).ok())
        .ok_or(MemoryImportError::UnsupportedMemory)?;
    // Section sizes are LEB128, so find the section header rather than assuming
    // a one-byte size or rewriting any bytes in subsequent sections.
    let section_start = section_header_start(bytes, &section_range)?;
    let mut converted = Vec::with_capacity(bytes.len() + maximum.len() + 5);
    converted.extend_from_slice(&bytes[..section_start]);
    converted.push(2);
    encode_u32(section_length, &mut converted);
    converted.extend_from_slice(&bytes[section_range.start..minimum_end]);
    let new_flags_offset = converted.len() - (minimum_end - flags_offset);
    converted[new_flags_offset] = 3;
    converted.extend_from_slice(&maximum);
    converted.extend_from_slice(&bytes[minimum_end..]);
    Ok(Cow::Owned(converted))
}

fn section_header_start(
    bytes: &[u8],
    content: &std::ops::Range<usize>,
) -> Result<usize, MemoryImportError> {
    // At most five bytes encode a u32 section length. Only the import
    // section's ID immediately precedes its size.
    let mut found = None;
    for header_start in content.start.saturating_sub(6)..content.start {
        if bytes[header_start] != 2 {
            continue;
        }
        let mut reader =
            BinaryReader::new(&bytes[header_start + 1..content.start], header_start + 1);
        if let Ok(size) = reader.read_var_u32()
            && reader.original_position() == content.start
            && usize::try_from(size).ok() == Some(content.len())
            && found.replace(header_start).is_some()
        {
            return Err(MemoryImportError::UnsupportedMemory);
        }
    }
    found.ok_or(MemoryImportError::UnsupportedMemory)
}

fn encode_u32(mut value: u32, output: &mut Vec<u8>) {
    while value >= 0x80 {
        output.push((value as u8 & 0x7f) | 0x80);
        value >>= 7;
    }
    output.push(value as u8);
}

#[cfg(test)]
#[path = "memory_import_tests.rs"]
mod tests;
