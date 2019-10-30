#ifndef STATE_H
#define STATE_H

enum class StateType { newMove, checkMove };
enum class Colour { NoColour, Black, White };
enum class Piece { Empty, Pawn, Bishop, Knight, Rook, Queen, King, NULLCell };

struct State {
	StateType type;  // See above
	Colour colour;   // What colour was the new piece?  (NOT what is my colour)
	Piece piece;  // The actual piece
};

#endif
