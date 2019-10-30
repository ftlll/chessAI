#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "queen.h"

Queen::Queen(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, true)
{}

Cell* Queen::copyCell() {
	Queen* cellPtr = new Queen(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

Info Queen::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::Queen;
	rtrnInfo.isPiece = isPiece;
	return rtrnInfo;
}

std::vector<chessMove> Queen::getPossibleMoves() {
	std::vector<chessMove> moveList;
	chessMove tempMove;
	tempMove.startPosition = std::make_pair(row, col);
	tempMove.startPiece = Piece::Queen;
	Info currInfo;
	std::vector<std::pair<int, int>> dirVec = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

	if (!isPiece) {
		return moveList;
	}

	for (int i = 0; i < dirVec.size(); ++i) {
		int j = 1;
		while (true) {
			currInfo = gameBoard[row + j * dirVec[i].first][col + j * dirVec[i].second]->getInfo();
			if (currInfo.piece == Piece::NULLCell) {
				break;
			}
			else if (currInfo.isPiece == false) {
				tempMove.whatMove = moveType::Move;
				tempMove.endPosition = std::make_pair(row + j * dirVec[i].first, col + j * dirVec[i].second);
				tempMove.endPiece = Piece::Empty;
				moveList.push_back(tempMove);
			}
			else if (currInfo.isPiece == true) {
				if (currInfo.colour != colour) {
					tempMove.whatMove = moveType::Capture;
					tempMove.endPosition = std::make_pair(row + j * dirVec[i].first, col + j * dirVec[i].second);
					tempMove.endPiece = currInfo.piece;
					moveList.push_back(tempMove);
				}
				break;
			}
			++j;
		}
	}

	return moveList;
}
