#include <stdexcept>
#include <vector>
#include <iostream>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "pawn.h"

Pawn::Pawn(int ro, int co, Colour clr, std::vector<std::vector<Cell*>>& gB, std::vector<chessMove>& mH) :
	Cell(ro, co, clr, gB, mH, true)
{}

Info Pawn::getInfo() {
	Info rtrnInfo;
	rtrnInfo.row = row;
	rtrnInfo.col = col;
	rtrnInfo.colour = colour;
	rtrnInfo.piece = Piece::Pawn;
	rtrnInfo.isPiece = isPiece;
	return rtrnInfo;
}

Cell* Pawn::copyCell() {
	Pawn* cellPtr = new Pawn(row, col, colour, gameBoard, moveHistory);
	cellPtr->isPiece = isPiece;
	cellPtr->hasMoved = hasMoved;
	Cell* rtrnPtr = dynamic_cast<Cell*>(cellPtr);
	return rtrnPtr;
}

std::vector<std::pair<int, int>> Pawn::getDirection() {
	if (colour == Colour::White) {
		std::vector<std::pair<int, int>> movePos = { {-1, 0}, {-1, -1}, {-1, 1}, {0, -1}, {0, 1} };
		return movePos;
	}
	else if (colour == Colour::Black) {
		std::vector<std::pair<int, int>> movePos = { {1, 0}, {1, -1}, {1, 1}, {0, -1}, {0, 1} };
		return movePos;
	}
	else if (colour == Colour::Red) {
		std::vector<std::pair<int, int>> movePos = { {0, 1}, {-1, 1}, {1, 1}, {-1, 0}, {1, 0} };
		return movePos;
	}
	else if (colour == Colour::Blue) {
		std::vector<std::pair<int, int>> movePos = { {0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0} };
		return movePos;
	}
}

bool Pawn::nextMovePromote(int rowInc, int colInc) {
	if (colour == Colour::White) {
		if ((row + rowInc) == 2) {
			return true;
		}
	}
	else if (colour == Colour::Black) {
		if ((row + rowInc) == 9) {
			return true;
		}
	}
	else if (colour == Colour::Red) {
		if ((col + colInc) == 9) {
			return true;
		}
	}
	else if (colour == Colour::Blue) {
		if ((col + colInc) == 2) {
			return true;
		}
	}
	return false;
}

void Pawn::nextMove(int rowInc, int colInc, moveType theMove, chessMove& tempMove, std::vector<chessMove>& moveList) {
	if (theMove == moveType::Move) {
		if (nextMovePromote(rowInc, colInc)) {
			tempMove.whatMove = moveType::PromotionMove;
			tempMove.promotion = Piece::Queen;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Rook;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Bishop;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Rook;
			moveList.push_back(tempMove);
		}
		else {
			tempMove.whatMove = moveType::Move;
			moveList.push_back(tempMove);
		}
	}
	else if (theMove == moveType::Capture) {
		if (nextMovePromote(rowInc, colInc)) {
			tempMove.whatMove = moveType::PromotionCapture;
			tempMove.promotion = Piece::Queen;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Rook;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Bishop;
			moveList.push_back(tempMove);
			tempMove.promotion = Piece::Rook;
			moveList.push_back(tempMove);
		}
		else {
			tempMove.whatMove = moveType::Capture;
			moveList.push_back(tempMove);
		}
	}
	else if (theMove == moveType::EnPassant) {
		tempMove.whatMove = moveType::EnPassant;
		moveList.push_back(tempMove);
	}
	else if (theMove == moveType::PawnDoubleJump) {
		tempMove.whatMove = moveType::PawnDoubleJump;
		moveList.push_back(tempMove);
	}
}

std::vector<chessMove> Pawn::getPossibleMoves() {
	std::vector<chessMove> moveList;
	Info currInfo;
	std::vector<std::pair<int, int>> movePos = getDirection();
	chessMove tempMove;
	chessMove EPtempMove;
	tempMove.startPosition = std::make_pair(row, col);
	tempMove.startPiece = Piece::Pawn;
	
	if (!isPiece) {
		return moveList;
	}

	currInfo = gameBoard[row + movePos[0].first][col + movePos[0].second]->getInfo();
	if (currInfo.isPiece == false and currInfo.piece != Piece::NULLCell) {
		tempMove.endPosition = std::make_pair(row + movePos[0].first, col + movePos[0].second);
		tempMove.endPiece = Piece::Empty;
		nextMove(movePos[0].first, movePos[0].second, moveType::Move, tempMove, moveList);
		currInfo = gameBoard[row + 2 * movePos[0].first][col + 2 * movePos[0].second]->getInfo();
		if (hasMoved == false and currInfo.piece != Piece::NULLCell and currInfo.isPiece == false) {
			tempMove.endPosition = std::make_pair(row + 2 * movePos[0].first, col + 2 * movePos[0].second);
			tempMove.endPiece = Piece::Empty;
			nextMove(2 * movePos[0].first, 2 * movePos[0].second, moveType::PawnDoubleJump, tempMove, moveList);
		}
	}

	currInfo = gameBoard[row + movePos[1].first][col + movePos[1].second]->getInfo();
	if (currInfo.colour != colour and currInfo.piece != Piece::NULLCell and currInfo.isPiece == true) {
		tempMove.endPosition = std::make_pair(row + movePos[1].first, col + movePos[1].second);
		tempMove.endPiece = currInfo.piece;
		nextMove(movePos[1].first, movePos[1].second, moveType::Capture, tempMove, moveList);
	}

	currInfo = gameBoard[row + movePos[2].first][col + movePos[2].second]->getInfo();
	if (currInfo.colour != colour and currInfo.piece != Piece::NULLCell and currInfo.isPiece == true) {
		tempMove.endPosition = std::make_pair(row + movePos[2].first, col + movePos[2].second);
		tempMove.endPiece = currInfo.piece;
		nextMove(movePos[2].first, movePos[2].second, moveType::Capture, tempMove, moveList);
	}

	if (moveHistory.size() != 0) {
		if (moveHistory.back().whatMove == moveType::PawnDoubleJump and moveHistory.back().endPosition == std::make_pair(row + movePos[3].first, col + movePos[3].second)) {
			currInfo = gameBoard[row + movePos[1].first][col + movePos[1].second]->getInfo();
			if (currInfo.piece != Piece::NULLCell and currInfo.isPiece == false) {
				tempMove.endPosition = std::make_pair(row + movePos[1].first, col + movePos[1].second);
				tempMove.endPiece = Piece::Empty;
				tempMove.extraPosition = std::make_pair(row + movePos[3].first, col + movePos[3].second);
				nextMove(movePos[1].first, movePos[1].second, moveType::EnPassant, tempMove, moveList);
			}
		}

		if (moveHistory.back().whatMove == moveType::PawnDoubleJump and moveHistory.back().endPosition == std::make_pair(row + movePos[4].first, col + movePos[4].second)) {
			currInfo = gameBoard[row + movePos[2].first][col + movePos[2].second]->getInfo();
			if (currInfo.piece != Piece::NULLCell and currInfo.isPiece == false) {
				tempMove.endPosition = std::make_pair(row + movePos[2].first, col + movePos[2].second);
				tempMove.endPiece = Piece::Empty;
				tempMove.extraPosition = std::make_pair(row + movePos[4].first, col + movePos[4].second);
				nextMove(movePos[2].first, movePos[2].second, moveType::EnPassant, tempMove, moveList);
			}
		}
	}
	
	return moveList;
}
