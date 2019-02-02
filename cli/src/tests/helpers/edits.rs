use super::random::Rand;
use tree_sitter::{InputEdit, Point, Tree};

pub struct Edit {
    pub position: usize,
    pub deleted_length: usize,
    pub inserted_text: Vec<u8>,
}

pub fn perform_edit(tree: &mut Tree, input: &mut Vec<u8>, edit: &Edit) {
    let start_byte = edit.position;
    let old_end_byte = edit.position + edit.deleted_length;
    let new_end_byte = edit.position + edit.inserted_text.len();
    let start_position = position_for_offset(input, start_byte);
    let old_end_position = position_for_offset(input, old_end_byte);
    input.splice(start_byte..old_end_byte, edit.inserted_text.iter().cloned());
    let new_end_position = position_for_offset(input, new_end_byte);
    tree.edit(&InputEdit {
        start_byte,
        old_end_byte,
        new_end_byte,
        start_position,
        old_end_position,
        new_end_position,
    });
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
        let mut deleted_length = rand.unsigned(10);
        if deleted_length > input.len() {
            deleted_length = input.len();
        }
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

fn position_for_offset(input: &Vec<u8>, offset: usize) -> Point {
    let mut result = Point { row: 0, column: 0 };
    for c in &input[0..offset] {
        if *c as char == '\n' {
            result.row += 1;
            result.column = 0;
        } else {
            result.column += 1;
        }
    }
    result
}
