use std::{borrow::Cow, str};

pub fn decode_utf8(input: Cow<[u8]>) -> Result<Cow<str>, (str::Utf8Error, Cow<[u8]>)> {
    match input {
        Cow::Borrowed(bytes) => {
            match str::from_utf8(bytes) {
                Ok(s) => Ok(s.into()),
                Err(e) => Err((e, Cow::Borrowed(bytes))),
            }
        }
        Cow::Owned(bytes) => {
            match String::from_utf8(bytes) {
                Ok(s) => Ok(s.into()),
                Err(e) => Err((e.utf8_error(), Cow::Owned(e.into_bytes()))),
            }
        }
    }
}

pub unsafe fn decode_utf8_unchecked(input: Cow<[u8]>, len: usize) -> Cow<str> {
    match input {
        Cow::Borrowed(bytes) => Cow::Borrowed(str::from_utf8_unchecked(&bytes[0..len])),
        Cow::Owned(mut bytes) => {
            bytes.truncate(len);
            Cow::Owned(String::from_utf8_unchecked(bytes))
        }
    }
}
