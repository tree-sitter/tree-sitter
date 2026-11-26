#[derive(Debug)]
pub struct ReadRecorder<'a> {
    content: &'a str,
    indices_read: Vec<usize>,
}

impl<'a> ReadRecorder<'a> {
    #[must_use]
    pub const fn new(content: &'a [u8]) -> Self {
        let Ok(content) = str::from_utf8(content) else {
            panic!("ReadRecorder requires UTF-8 text");
        };
        Self {
            content,
            indices_read: Vec::new(),
        }
    }

    pub fn read(&mut self, offset: usize) -> &'a [u8] {
        if offset >= self.content.len() {
            return &[];
        }

        let c = self.content[offset..].chars().next().unwrap();
        let end = offset + c.len_utf8();
        for index in offset..end {
            if let Err(i) = self.indices_read.binary_search(&index) {
                self.indices_read.insert(i, index);
            }
        }
        &self.content.as_bytes()[offset..end]
    }

    pub fn strings_read(&self) -> Vec<&'a str> {
        let Some((&first, rest)) = self.indices_read.split_first() else {
            return Vec::new();
        };
        let mut result = Vec::new();
        let mut range = first..first + 1;
        for &index in rest {
            if index == range.end {
                range.end += 1;
            } else {
                result.push(&self.content[range]);
                range = index..index + 1;
            }
        }
        result.push(&self.content[range]);
        result
    }
}
