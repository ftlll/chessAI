#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "nullcell.h"

NULLCell::NULLCell(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, false)
{}

Cell* NULLCell::copyCell() {
	NULLCell* cellPtr = new NULLCell(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

std::vector<chessMove> NULLCell::getPossibleMoves() {
	std::vector<chessMove> moveList;
	return moveList;
}

Info NULLCell::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::NULLCell;
	rtrnInfo.isPiece = isPiece;
	return rtrnInfo;
}
