#include <stdexcept>
#include <iostream>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "knight.h"

Knight::Knight(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, true)
{}

Cell* Knight::copyCell() {
	Knight* cellPtr = new Knight(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

Info Knight::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::Knight;
	rtrnInfo.isPiece = isPiece;
	return rtrnInfo;
}

std::vector<chessMove> Knight::getPossibleMoves() {
	std::vector<chessMove> moveList;
	chessMove tempMove;
	tempMove.startPosition = std::make_pair(row, col);
	tempMove.startPiece = Piece::Pawn;
	Info currInfo;
	std::vector<std::pair<int, int>> movePos = { {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };

	if (!isPiece) {
		return moveList;
	}

	for (int i = 0; i < movePos.size(); ++i) {
		currInfo = gameBoard[row + movePos[i].first][col + movePos[i].second]->getInfo();
		//std::cout << row + movePos[i].first << " " << col + movePos[i].second << std::endl;
		if (currInfo.piece != Piece::NULLCell) {
			//std::cout << row + movePos[i].first << " " << col + movePos[i].second << std::endl;
			if (currInfo.isPiece) {
				if (currInfo.colour != colour) {
					tempMove.whatMove = moveType::Capture;
					tempMove.endPosition = std::make_pair(row + movePos[i].first, col + movePos[i].second);
					tempMove.endPiece = currInfo.piece;
					moveList.push_back(tempMove);
				}
			}
			else {
				tempMove.whatMove = moveType::Move;
				tempMove.endPosition = std::make_pair(row + movePos[i].first, col + movePos[i].second);
				tempMove.endPiece = Piece::Empty;
				moveList.push_back(tempMove);
			}
		}
	}
	return moveList;
}
