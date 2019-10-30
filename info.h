#ifndef __INFO_H__
#define __INFO_H__

enum class Colour { NoColour, Black, White, Red, Blue };
enum class Piece { Empty, Pawn, Bishop, Knight, Rook, Queen, King, NULLCell };

struct Info {
	int row;
	int col;
	Colour colour;
	Piece piece;
	bool isPiece;
};
#endif
