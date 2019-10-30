#ifndef MOVE_H
#define MOVE_H
#include<vector>
#include "info.h"

enum class moveType { Move, PawnDoubleJump, Capture, Castle, EnPassant, PromotionMove, PromotionCapture };

struct chessMove {
	moveType whatMove;
	std::pair<int, int> startPosition;
	Piece startPiece;
	std::pair<int, int> endPosition;
	Piece endPiece;
	Piece promotion;
	std::pair<int, int> extraPosition;
	std::pair<int, int> extraEndPosition;
};

#endif
