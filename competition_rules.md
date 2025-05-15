# Name Pending

## Basics

### Arbiter

The arbiter can be any one of us, or we can have Kohli and his machine be the organizer.

### Language and Allowed Libraries

Any programming language is allowed. In those languages, unrestricted use of the standard library is allowed.

Using a chess library is NOT allowed. This means that there cannot be a third-party library that does

- search and evaluation, and
- board representation.

The board representation part of your engine must be code that you wrote, and the same goes for the search and evaluation (the heart and soul of any engine).

You may look at any books (online or otherwise) and blogs and any materials as reference. But copying code from other sources, is not allowed. So, for example, if you're writing your engine in C++, you can look at how Stockfish handles things, but copying their board representation word for word would be a big no-no.

## Format of the Final Test

The rules will be very similar to standard [TCEC rules](https://wiki.chessdom.org/Rules).

The Time Control, Game Ending, and Tiebreaks will be the same as TCEC. For convenience, we will mention the rules below:

> 1. Time control
>
> - Time control for all stages will be 30 mins + 3 secs increment per move for all games in a match.
> - If an engine loses on time, that results in a loss and will be registered as such. The game will not be replayed.
>
> 2. Game ending
>
> - A game can be won by mate, opponent's illegal move, opponent's resignation or opponent loses on time.
> - A game can end in a draw by three-fold repetition, 50-move rule or stalemate.
> - If an engine loses on time, the result will not be changed or the game replayed.
>
> 3. Tiebreaks
>
> - If necessary, tiebreaks shall be used to determine advancement, based on the final standings of a League or Division. For all Events except the MiniTinal, the following criteria will be used, in the order as presented below:
>   - In case of engines being tied, then the direct encounter(s) between the tied engines decides first.
>   - The Sonneborn-Berger is the second criterion.
>   - r-mobility tiebreak is the third criterion.
>   - Fourth criterion is greatest number of double wins (winning both sides of a game pair and/or book exit)
>   - Fifth criterion is lowest average number of moves in won games
>   - Sixth criterion is highest average number of moves in lost games
> - In case the MiniFinal ends in a tie after 50 games, pairs of games at the same time control will be played until one engine wins such a pair.

Note that the 7th tiebreaker criteria was removed, as it is not relevant to a two-team competition.

### Opening Book

In TCEC, the organizers choose an opening book each year, and it's used by both engines. Engines are not allowed to bring their own opening books, and those that do are immediately disqualified.

More information about how the opening books are made each year can be found [here](https://tcec-chess.com/articles/TCEC_Openings_FAQ.html).

For our competition, we will use the TCEC 26 Premier Division book, which can be found [on their blog](https://blogchess2016.blogspot.com/2024/06/noomen-tcec-26-books-available.html).

### Endgame Tablebase

In TCEC, they also don't allow bespoke endgame tablebases and supply that information to the engines. They use 6-man tablebases, which have very steep space requirements (68.3 GiB according to [this website](https://chess.massimilianogoi.com/download/tablebases/)).

In the interest of fairness and practicality, we will use 5-man tablebases (which are a much more reasonable 1 GiB in size). The endgame tablebase can be downloaded from [here](https://chess.massimilianogoi.com/download/tablebases/Syzygy3-4-5/).

### Miscellaneous Rules

Two rules which I feel deserve special mention are

- No pondering. This means that while the other engine is playing, your engine cannot "think" about its next move. This is done to ensure fairness and prevent resource (CPU time, RAM) hogging, which can impact the play level of your opponent's engine.
- No concurrency. We will have both engines play one game at a time. Again, this is done to prevent resource hogging.

### Potential Modifications

The main modification we can have is the time control. 30+3 is a very long time control, which might take a day or two to run for a total of 50 games. We need to have a high number of games to ensure no bias and to determine a clear winner, but we can reduce the time control to 5+3 or so.