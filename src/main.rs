use scylla_chess::bitboard::Bitboard;

fn main() {
    let mut b = Bitboard::new();

    b.set(2, 4); // Square C5

    println!("{}", b);
}
