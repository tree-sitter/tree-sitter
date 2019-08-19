use rand::distributions::Alphanumeric;
use rand::prelude::{Rng, SeedableRng, StdRng};

const OPERATORS: &[char] = &[
    '+', '-', '<', '>', '(', ')', '*', '/', '&', '|', '!', ',', '.',
];

pub struct Rand(StdRng);

impl Rand {
    pub fn new(seed: usize) -> Self {
        Rand(StdRng::seed_from_u64(seed as u64))
    }

    pub fn unsigned(&mut self, max: usize) -> usize {
        self.0.gen_range(0, max + 1)
    }

    pub fn words(&mut self, max_count: usize) -> Vec<u8> {
        let mut result = Vec::new();
        let word_count = self.unsigned(max_count);
        for i in 0..word_count {
            if i > 0 {
                if self.unsigned(5) == 0 {
                    result.push('\n' as u8);
                } else {
                    result.push(' ' as u8);
                }
            }
            if self.unsigned(3) == 0 {
                let index = self.unsigned(OPERATORS.len() - 1);
                result.push(OPERATORS[index] as u8);
            } else {
                for _ in 0..self.unsigned(8) {
                    result.push(self.0.sample(Alphanumeric) as u8);
                }
            }
        }
        result
    }
}
