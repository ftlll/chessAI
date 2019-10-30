#include <stdexcept>
#include <iostream>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "king.h"

King::King(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, true)
{}

Info King::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::King;
	rtrnInfo.isPiece = isPiece;
	return rtrnInfo;
}

Cell* King::copyCell() {
	King* cellPtr = new King(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

std::vector<std::pair<int, int>> King::getDirection() {
	std::vector<std::pair<int, int>> casPos = { {0, 1}, {0, 2}, {0, 3}, {0, -1}, {0, -2}, {0, -3}, {0, -4} };
	return casPos;
}

std::vector<chessMove> King::getPossibleMoves() {
	std::vector<chessMove> moveList;
	chessMove tempMove;
	tempMove.startPosition = std::make_pair(row, col);
	tempMove.startPiece = Piece::King;
	Info currInfo;
	std::vector<std::pair<int, int>> movePos = { {0, 1}, {0, -1}, {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1} };
	std::vector<std::pair<int, int>> casPos = getDirection();

	if (!isPiece) {
		return moveList;
	}

	for (int i = 0; i < movePos.size(); ++i) {
		currInfo = gameBoard[row + movePos[i].first][col + movePos[i].second]->getInfo();
		if (currInfo.isPiece == true and currInfo.piece != Piece::NULLCell and currInfo.colour != colour) {
			tempMove.whatMove = moveType::Capture;
			tempMove.endPosition = std::make_pair(row + movePos[i].first, col + movePos[i].second);
			tempMove.endPiece = currInfo.piece;
			moveList.push_back(tempMove);
		}
		else if (currInfo.isPiece == false and currInfo.piece != Piece::NULLCell) {
			tempMove.whatMove = moveType::Move;
			tempMove.endPosition = std::make_pair(row + movePos[i].first, col + movePos[i].second);
			tempMove.endPiece = Piece::Empty;
			moveList.push_back(tempMove);
		}
	}

	if (hasMoved == false) {
		if (gameBoard[row + casPos[0].first][col + casPos[0].second]->isOccupied() == false and 
			gameBoard[row + casPos[1].first][col + casPos[1].second]->isOccupied() == false) {
			currInfo = gameBoard[row + casPos[2].first][col + casPos[2].second]->getInfo();
			if (currInfo.colour == colour and currInfo.piece == Piece::Rook and gameBoard[row + casPos[2].first][col + casPos[2].second]->conductMove() == false and currInfo.isPiece == true) {
				tempMove.whatMove = moveType::Castle;
				tempMove.endPosition = std::make_pair(row + casPos[1].first, col + casPos[1].second);
				tempMove.endPiece = Piece::Empty;
				tempMove.extraPosition = std::make_pair(row + casPos[2].first, col + casPos[2].second);//For rook
				tempMove.extraEndPosition = std::make_pair(row + casPos[0].first, col + casPos[0].second);//For rook ending position
				moveList.push_back(tempMove);
			}
		}

		if (gameBoard[row + casPos[3].first][col + casPos[3].second]->isOccupied() == false and
			gameBoard[row + casPos[4].first][col + casPos[4].second]->isOccupied() == false and
			gameBoard[row + casPos[5].first][col + casPos[5].second]->isOccupied() == false) {
			currInfo = gameBoard[row + casPos[6].first][col + casPos[6].second]->getInfo();
			if (currInfo.colour == colour and currInfo.piece == Piece::Rook and gameBoard[row + casPos[6].first][col + casPos[6].second]->conductMove() == false and currInfo.isPiece == true) {
				tempMove.whatMove = moveType::Castle;
				tempMove.endPosition = std::make_pair(row + casPos[4].first, col + casPos[4].second);
				tempMove.endPiece = Piece::Empty;
				tempMove.extraPosition = std::make_pair(row + casPos[6].first, col + casPos[6].second);//For rook
				tempMove.extraEndPosition = std::make_pair(row + casPos[3].first, col + casPos[3].second);//For rook ending position
				moveList.push_back(tempMove);
			}
		}
	}

	return moveList;
}
