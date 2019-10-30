#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"

Cell::Cell(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH, bool ip) :
	row(ro),
	col(co),
	colour(clr),
	gameBoard(gB),
	moveHistory(mH),
	isPiece(ip),
	hasMoved(false)
{}

bool Cell::conductMove() {
	return hasMoved;
}

void Cell::moveCell() {
	hasMoved = true;
}

void Cell::captureCell() {
	isPiece = false;
}

bool Cell::isOccupied() {
	return isPiece;
}

void Cell::updateRC(int newRow, int newCol) {
	row = newRow;
	col = newCol;
}
