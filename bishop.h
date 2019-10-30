#ifndef BISHOP_H
#define BISHOP_H
#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"

class Bishop : public Cell {

public:
	Bishop(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH);
	std::vector<chessMove> getPossibleMoves() override;
	Info getInfo() override;
	Cell* copyCell() override;
};
#endif
