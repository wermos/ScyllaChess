use scylla_chess::bitboard::Bitboard;

fn main() {
    let mut b = Bitboard::new();

    b.set(2, 4); // Square C5

    println!("{}", b);

    // let mut ans: u64 = 1 << 32;
    // let mask = 1 << 5;

    // ans |= mask;

    // let occ = (ans >> 5) & 1;

    // println!("Number: {:b}\t Mask: {:b}\nOccupancy: {}", ans, mask, occ);
}
