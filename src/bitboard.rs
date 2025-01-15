use std::ops::{Index, IndexMut};

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
}

// impl fmt::Display for Bitboard {
//     fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        
//     }
// }
