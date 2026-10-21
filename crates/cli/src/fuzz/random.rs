const OPERATORS: &[char] = &[
    '+', '-', '<', '>', '(', ')', '*', '/', '&', '|', '!', ',', '.', '%',
];

const ALPHANUMERIC: &[u8] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

/// `SplitMix64`, deterministic per seed so a failing run replays with `TREE_SITTER_SEED`.
pub struct Rand(u64);

impl Rand {
    #[must_use]
    pub const fn new(seed: usize) -> Self {
        Self(seed as u64)
    }

    const fn next_u64(&mut self) -> u64 {
        self.0 = self.0.wrapping_add(0x9E37_79B9_7F4A_7C15);
        let mut mixed = self.0;
        mixed = (mixed ^ (mixed >> 30)).wrapping_mul(0xBF58_476D_1CE4_E5B9);
        mixed = (mixed ^ (mixed >> 27)).wrapping_mul(0x94D0_49BB_1331_11EB);
        mixed ^ (mixed >> 31)
    }

    pub fn unsigned(&mut self, max: usize) -> usize {
        let value = self.next_u64();
        (max as u64)
            .checked_add(1)
            .map_or(value, |bound| value % bound) as usize
    }

    pub fn chance(&mut self, probability: f64) -> bool {
        ((self.next_u64() >> 11) as f64 / (1u64 << 53) as f64) < probability
    }

    pub fn words(&mut self, max_count: usize) -> Vec<u8> {
        let word_count = self.unsigned(max_count);
        let mut result = Vec::with_capacity(2 * word_count);
        for i in 0..word_count {
            if i > 0 {
                if self.unsigned(5) == 0 {
                    result.push(b'\n');
                } else {
                    result.push(b' ');
                }
            }
            if self.unsigned(3) == 0 {
                let index = self.unsigned(OPERATORS.len() - 1);
                result.push(OPERATORS[index] as u8);
            } else {
                for _ in 0..self.unsigned(8) {
                    result.push(ALPHANUMERIC[self.unsigned(ALPHANUMERIC.len() - 1)]);
                }
            }
        }
        result
    }
}
