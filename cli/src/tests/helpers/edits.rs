use super::random::Rand;
use crate::parse::Edit;
use std::ops::Range;
use std::str;

#[derive(Debug)]
pub struct ReadRecorder<'a> {
    content: &'a Vec<u8>,
    indices_read: Vec<usize>,
}

impl<'a> ReadRecorder<'a> {
    pub fn new(content: &'a Vec<u8>) -> Self {
        Self {
            content,
            indices_read: Vec::new(),
        }
    }

    pub fn read(&mut self, offset: usize) -> &'a [u8] {
        if offset < self.content.len() {
            if let Err(i) = self.indices_read.binary_search(&offset) {
                self.indices_read.insert(i, offset);
            }
            &self.content[offset..(offset + 1)]
        } else {
            &[]
        }
    }

    pub fn strings_read(&self) -> Vec<&'a str> {
        let mut result = Vec::new();
        let mut last_range: Option<Range<usize>> = None;
        for index in self.indices_read.iter() {
            if let Some(ref mut range) = &mut last_range {
                if range.end == *index {
                    range.end += 1;
                } else {
                    result.push(str::from_utf8(&self.content[range.clone()]).unwrap());
                    last_range = None;
                }
            } else {
                last_range = Some(*index..(*index + 1));
            }
        }
        if let Some(range) = last_range {
            result.push(str::from_utf8(&self.content[range.clone()]).unwrap());
        }
        result
    }
}

pub fn invert_edit(input: &Vec<u8>, edit: &Edit) -> Edit {
    let position = edit.position;
    let removed_content = &input[position..(position + edit.deleted_length)];
    Edit {
        position,
        deleted_length: edit.inserted_text.len(),
        inserted_text: removed_content.to_vec(),
    }
}

pub fn get_random_edit(rand: &mut Rand, input: &Vec<u8>) -> Edit {
    let choice = rand.unsigned(10);
    if choice < 2 {
        // Insert text at end
        let inserted_text = rand.words(3);
        Edit {
            position: input.len(),
            deleted_length: 0,
            inserted_text,
        }
    } else if choice < 5 {
        // Delete text from the end
        let deleted_length = rand.unsigned(30).min(input.len());
        Edit {
            position: input.len() - deleted_length,
            deleted_length,
            inserted_text: vec![],
        }
    } else if choice < 8 {
        // Insert at a random position
        let position = rand.unsigned(input.len());
        let word_count = 1 + rand.unsigned(3);
        let inserted_text = rand.words(word_count);
        Edit {
            position,
            deleted_length: 0,
            inserted_text,
        }
    } else {
        // Replace at random position
        let position = rand.unsigned(input.len());
        let deleted_length = rand.unsigned(input.len() - position);
        let word_count = 1 + rand.unsigned(3);
        let inserted_text = rand.words(word_count);
        Edit {
            position,
            deleted_length,
            inserted_text,
        }
    }
}
