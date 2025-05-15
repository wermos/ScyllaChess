use std::fmt;

#[derive(Clone, Debug)]
pub struct Bitboard {
    pub board: u64,
}

impl Bitboard {
    pub fn new() -> Self {
        Self {
            board: 0,
        }
    }

    pub fn set(&mut self, i: usize, j: usize) {
        let idx = i * 8 + j;
        let mask = 1 << idx;

        self.board |= mask;
    }

    pub fn get(&self, i: usize, j: usize) -> bool {
        let idx = i * 8 + j;

        let occupancy = (self.board >> idx) & 1;

        if occupancy == 1 {
            true
        } else {
            false
        }
    }
}

impl fmt::Display for Bitboard {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for i in (0..8).rev() {
            for j in 0..8 {
                if self.get(i, j) {
                    write!(f, "1 ")?;
                } else {
                    write!(f, "0 ")?;
                }
            }
            writeln!(f)?;
        }

        writeln!(f)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_get_set() {
        let mut b = Bitboard::new();

        b.set(0, 1); // Square B1
        b.set(4, 5); // Square F5

        assert_eq!(b.board, 0x000000002000000002);
        
        let ans = b.get(4, 5);

        assert_eq!(ans, true);
    }
}