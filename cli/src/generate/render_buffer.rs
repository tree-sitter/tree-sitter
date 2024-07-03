use std::io::Write;
use std::mem::swap;


pub struct RenderBuffer {
    pub indent_width: usize,
    pub indent_level: usize,
    text: String, 
}


impl RenderBuffer {
    pub fn new(indent_width: usize) -> Self {
        Self {
            indent_width,
            indent_level: 0,
            text: String::new(),
        }
    }

    pub fn add_newline(&mut self) {
        self.text += "\n"
    }

    pub fn add_whitespace(&mut self) {
        for _ in 0 .. self.indent_width * self.indent_level {
            self.text += " "
        }
    }

    pub fn indent(&mut self, delta: usize) {
        self.indent_level += delta;
    }

    pub fn dedent(&mut self, delta: usize) {
        assert!(self.indent_level >= delta);
        self.indent_level -= delta;
    }

    pub fn append(&mut self, text: String) {
        self.text += text.as_ref()
    }

    pub fn swap_text(&mut self, text: String) -> String {
        let mut text = text;
        swap(&mut text, &mut self.text);
        text
    }

    pub fn get_text(&mut self) -> String {
        self.swap_text(String::new())
    }
}


impl Write for RenderBuffer {
    fn write(&mut self, bytes: &[u8]) -> Result<usize, std::io::Error> {
        // dubious
        for byte in bytes.iter() {
            self.text.push(char::from_u32(*byte as u32).unwrap());
        }
        Ok(bytes.len())
    }
    fn flush(&mut self) -> Result<(), std::io::Error> {
        self.text.clear();
        Ok(())
    }
}
