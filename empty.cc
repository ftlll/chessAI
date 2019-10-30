#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "empty.h"

Empty::Empty(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, false)
{}

Cell* Empty::copyCell() {
	Empty* cellPtr = new Empty(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

std::vector<chessMove> Empty::getPossibleMoves() {
	std::vector<chessMove> moveList;
	return moveList;
}

Info Empty::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::Empty;
	rtrnInfo.isPiece = false;
	return rtrnInfo;
}
