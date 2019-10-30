#ifndef CELL_H
#define CELL_H
#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"

class Cell {
protected:
	int row;
	int col;
	Colour colour;
	std::vector<std::vector<Cell*>>& gameBoard;
	std::vector<chessMove>& moveHistory;
	bool isPiece;
	bool hasMoved;

 public:
	Cell(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH, bool ip);
	virtual std::vector<chessMove> getPossibleMoves() = 0;
	virtual Info getInfo() = 0;
	virtual Cell* copyCell() = 0;
	void moveCell();
	void captureCell();
	bool conductMove();
	bool isOccupied();
	void updateRC(int newRow, int newCol);
};
#endif
