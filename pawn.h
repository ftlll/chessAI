#ifndef PAWN_H
#define PAWN_H
#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"

class Pawn: public Cell {
	std::vector<std::pair<int, int>> getDirection();
	bool nextMovePromote(int rowInc, int colInc);
	void nextMove(int rowInc, int colInc, moveType theMove, chessMove& tempMove, std::vector<chessMove>& moveList);
public:
	Pawn(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH);
	std::vector<chessMove> getPossibleMoves() override;
	Info getInfo() override;
	Cell* copyCell() override;
};
#endif
