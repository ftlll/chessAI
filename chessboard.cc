#include <stdexcept>
#include <vector>
#include <algorithm>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"
#include "empty.h"
#include "nullcell.h"
#include "chessboard.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;

std::vector<chessMove> chessBoard::getColourNextMove(Colour requiredColour) {
	std::vector<chessMove> tempMoves;
	std::vector<chessMove> validMoves;
	Info currInfo;
	for (int i = 0; i < gameBoard.size(); ++i) {
		for (int j = 0; j < gameBoard[i].size(); ++j) {
			currInfo = gameBoard[i][j]->getInfo();
			if (currInfo.isPiece and currInfo.colour == requiredColour) {
				tempMoves = gameBoard[i][j]->getPossibleMoves();
				validMoves.insert(validMoves.end(), tempMoves.begin(), tempMoves.end());
			}
		}
	}
	return validMoves;
}

bool chessBoard::validateMove(std::vector<chessMove> futureMoves) {
	for (int i = 0; i < futureMoves.size(); ++i) {
		if (futureMoves[i].endPiece == Piece::King) {
			return false;
		}
	}
	return true;
}

bool chessBoard::isAvoidCaptureMove(std::vector<chessMove>& futureMoves) {
	for (int i = 0; i < futureMoves.size(); ++i) {
		if (futureMoves[i].whatMove == moveType::Capture or futureMoves[i].whatMove == moveType::PromotionCapture) {
			return false;
		}
	}
	return true;
}

void chessBoard::updatePM() {
	std::vector<chessMove> validMoves;
	std::vector<chessMove> futureMoves;
	possibleMoves.clear();
	validMoves = getColourNextMove(currentColour);
	for (int i = 0; i < validMoves.size(); ++i) {
		makeTempMove(validMoves[i]);
		if (currentColour == Colour::White) {
			futureMoves = getColourNextMove(Colour::Black);
		}
		else if (currentColour == Colour::Black) {
			futureMoves = getColourNextMove(Colour::White);
		}
		if (validateMove(futureMoves)) {
			if (validMoves[i].whatMove == moveType::Castle) {
				undoTempMove();
				if (currentColour == Colour::White) {
					futureMoves = getColourNextMove(Colour::Black);
				}
				else if (currentColour == Colour::Black) {
					futureMoves = getColourNextMove(Colour::White);
				}
				if (validateMove(futureMoves)) {
					chessMove castleIntermediate;
					castleIntermediate.whatMove = moveType::Move;
					castleIntermediate.startPosition = validMoves[i].startPosition;
					castleIntermediate.endPosition = validMoves[i].extraEndPosition;
					makeTempMove(castleIntermediate);
					if (currentColour == Colour::White) {
						futureMoves = getColourNextMove(Colour::Black);
					}
					else if (currentColour == Colour::Black) {
						futureMoves = getColourNextMove(Colour::White);
					}
					if (validateMove(futureMoves)) {
						possibleMoves.push_back(validMoves[i]);
					}
					undoTempMove();
				}
			}
			else {
				possibleMoves.push_back(validMoves[i]);
				undoTempMove();
			}
		}
		else {
			undoTempMove();
		}
	}
}

void chessBoard::makeTempMove(chessMove theMove) {
	Cell* newPtr;
	Cell* tempPtr;
	lastMove.clear();
	if (theMove.whatMove == moveType::Move) {
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		tempPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		gameBoard[theMove.endPosition.first][theMove.endPosition.second] = tempPtr;
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->updateRC(theMove.endPosition.first, theMove.endPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::PawnDoubleJump) {
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		tempPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		gameBoard[theMove.endPosition.first][theMove.endPosition.second] = tempPtr;
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->updateRC(theMove.endPosition.first, theMove.endPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::Capture) {
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		tempPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		gameBoard[theMove.endPosition.first][theMove.endPosition.second] = tempPtr;
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->updateRC(theMove.endPosition.first, theMove.endPosition.second);
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->captureCell();
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::EnPassant) {
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		newPtr = gameBoard[theMove.extraPosition.first][theMove.extraPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.extraPosition, newPtr));
		tempPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		gameBoard[theMove.endPosition.first][theMove.endPosition.second] = tempPtr;
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->updateRC(theMove.endPosition.first, theMove.endPosition.second);
		gameBoard[theMove.extraPosition.first][theMove.extraPosition.second]->captureCell();
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::PromotionMove) {
		Colour promotionColour = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->getInfo().colour;
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		delete gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		if (theMove.promotion == Piece::Queen) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Queen(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Bishop) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Bishop(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Rook) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Rook(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Knight) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Knight(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::PromotionCapture) {
		Colour promotionColour = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->getInfo().colour;
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		delete gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		if (theMove.promotion == Piece::Queen) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Queen(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Bishop) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Bishop(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Rook) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Rook(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		else if (theMove.promotion == Piece::Knight) {
			gameBoard[theMove.endPosition.first][theMove.endPosition.second] = new Knight(theMove.endPosition.first, theMove.endPosition.second, promotionColour, gameBoard, moveHistory);
		}
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->captureCell();
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
	}
	else if (theMove.whatMove == moveType::Castle) {
		newPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.startPosition, newPtr));
		newPtr = gameBoard[theMove.endPosition.first][theMove.endPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.endPosition, newPtr));
		newPtr = gameBoard[theMove.extraPosition.first][theMove.extraPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.extraPosition, newPtr));
		newPtr = gameBoard[theMove.extraEndPosition.first][theMove.extraEndPosition.second]->copyCell();
		lastMove.push_back(std::make_pair(theMove.extraEndPosition, newPtr));
		tempPtr = gameBoard[theMove.startPosition.first][theMove.startPosition.second];
		gameBoard[theMove.startPosition.first][theMove.startPosition.second] = gameBoard[theMove.endPosition.first][theMove.endPosition.second];
		gameBoard[theMove.endPosition.first][theMove.endPosition.second] = tempPtr;
		tempPtr = gameBoard[theMove.extraPosition.first][theMove.extraPosition.second];
		gameBoard[theMove.extraPosition.first][theMove.extraPosition.second] = gameBoard[theMove.extraEndPosition.first][theMove.extraEndPosition.second];
		gameBoard[theMove.extraEndPosition.first][theMove.extraEndPosition.second] = tempPtr;
		gameBoard[theMove.startPosition.first][theMove.startPosition.second]->updateRC(theMove.startPosition.first, theMove.startPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->updateRC(theMove.endPosition.first, theMove.endPosition.second);
		gameBoard[theMove.extraPosition.first][theMove.extraPosition.second]->updateRC(theMove.extraPosition.first, theMove.extraPosition.second);
		gameBoard[theMove.extraEndPosition.first][theMove.extraEndPosition.second]->updateRC(theMove.extraEndPosition.first, theMove.extraEndPosition.second);
		gameBoard[theMove.endPosition.first][theMove.endPosition.second]->moveCell();
		gameBoard[theMove.extraEndPosition.first][theMove.extraEndPosition.second]->moveCell();
	}
}

void chessBoard::undoTempMove() {
	for (int i = 0; i < lastMove.size(); ++i) {
		delete gameBoard[lastMove[i].first.first][lastMove[i].first.second];
		gameBoard[lastMove[i].first.first][lastMove[i].first.second] = lastMove[i].second;
	}
	lastMove.clear();
}

void chessBoard::printPossibleMoves() {
	std::cout << possibleMoves.size() << std::endl;
	for (int i = 0; i < possibleMoves.size(); ++i) {
		std::cout << possibleMoves[i].startPosition.first << " " << possibleMoves[i].startPosition.second;
		std::cout << " " << possibleMoves[i].endPosition.first << " " << possibleMoves[i].endPosition.second << std::endl;
	}
}

std::vector<chessMove> chessBoard::getPossibleMoves() {
	return possibleMoves;
}

std::vector<chessMove> chessBoard::getAvoidCaptureMoves() {
	std::vector<chessMove> futureMoves;
	std::vector<chessMove> nocapMoves;
	for (int i = 0; i < possibleMoves.size(); ++i) {
		makeTempMove(possibleMoves[i]);
		if (currentColour == Colour::White) {
			futureMoves = getColourNextMove(Colour::Black);
		}
		else if (currentColour == Colour::Black) {
			futureMoves = getColourNextMove(Colour::White);
		}
		if (isAvoidCaptureMove(futureMoves)) {
			nocapMoves.push_back(possibleMoves[i]);
		}
		undoTempMove();
	}
	return nocapMoves;
}

int chessBoard::getPieceValue(Piece thePiece) {
	if (thePiece == Piece::Pawn) {
		return 1;
	}
	else if (thePiece == Piece::Bishop or thePiece == Piece::Knight) {
		return 3;
	}
	else if (thePiece == Piece::Rook) {
		return 5;
	}
	else if (thePiece == Piece::Queen) {
		return 9;
	}
	else if (thePiece == Piece::King) {
		return 100;
	}
}

int chessBoard::getMaxDrawback(std::vector<chessMove> futureMoves) {
	int maxDrawback = 0;
	int currDrawback = 0;
	for (int i = 0; i < futureMoves.size(); ++i) {
		currDrawback = 0;
		if (futureMoves[i].whatMove == moveType::PromotionCapture or futureMoves[i].whatMove == moveType::PromotionMove) {
			currDrawback += getPieceValue(futureMoves[i].promotion);
		}
		if (futureMoves[i].whatMove == moveType::PromotionCapture or futureMoves[i].whatMove == moveType::Capture) {
			currDrawback += getPieceValue(futureMoves[i].endPiece);
		}
		if (futureMoves[i].whatMove == moveType::EnPassant) {
			currDrawback += 1;
		}
		maxDrawback = std::max(maxDrawback, currDrawback);
	}
	return maxDrawback;
}

std::vector<chessMove> chessBoard::getPositiveMoves() {
	std::vector<chessMove> futureMoves;
	std::vector<chessMove> bestMoves;
	int bestOutcome = -1000;
	int difference;
	for (int i = 0; i < possibleMoves.size(); ++i) {
		difference = 0;
		if (possibleMoves[i].whatMove == moveType::PromotionCapture or possibleMoves[i].whatMove == moveType::PromotionMove) {
			difference += getPieceValue(possibleMoves[i].promotion);
		}
		if (possibleMoves[i].whatMove == moveType::PromotionCapture or possibleMoves[i].whatMove == moveType::Capture) {
			difference += getPieceValue(possibleMoves[i].endPiece);
		}
		if (possibleMoves[i].whatMove == moveType::EnPassant) {
			difference += 1;
		}
		makeTempMove(possibleMoves[i]);
		if (currentColour == Colour::White) {
			futureMoves = getColourNextMove(Colour::Black);
		}
		else if (currentColour == Colour::Black) {
			futureMoves = getColourNextMove(Colour::White);
		}
		difference -= getMaxDrawback(futureMoves);
		if (difference > bestOutcome) {
			bestMoves.clear();
			bestMoves.push_back(possibleMoves[i]);
			bestOutcome = difference;
		}
		else if (difference == bestOutcome) {
			bestMoves.push_back(possibleMoves[i]);
		}
		undoTempMove();
	}
	return bestMoves;
}

bool chessBoard::isCheckMove(chessMove theMove) {
	Colour theMoveColour = gameBoard[theMove.startPosition.first][theMove.startPosition.second]->getInfo().colour;
	makeTempMove(theMove);
	std::vector<chessMove> immediateNextMove = getColourNextMove(theMoveColour);
	undoTempMove();
	if (validateMove(immediateNextMove) == false) {
		return true;
	}
	return false;
}

bool chessBoard::isStalemate() {
	if (possibleMoves.size() == 0) {
		return true;
	}
	return false;
}

bool chessBoard::isCheckmate() {
	return isStalemate() and prevMoveIsCheck;
}

void chessBoard::undoMove() {
	for (int i = 0; i < moveStack.back().size(); ++i) {
		delete gameBoard[moveStack.back()[i].first.first][moveStack.back()[i].first.second];
		gameBoard[moveStack.back()[i].first.first][moveStack.back()[i].first.second] = moveStack.back()[i].second;
	}
	moveStack.pop_back();
	moveHistory.pop_back();
	if (currentColour == Colour::White) {
		currentColour = Colour::Black;
	}
	else if (currentColour == Colour::Black) {
		currentColour = Colour::White;
	}
	updatePM();
	//printPossibleMoves();
	updateTD();
}

void chessBoard::makeMove(chessMove theMove) {
	for (int i = 0; i < possibleMoves.size(); ++i) {
		if (possibleMoves[i].startPosition == theMove.startPosition and possibleMoves[i].endPosition == theMove.endPosition) {
			if (possibleMoves[i].whatMove == moveType::PromotionMove || possibleMoves[i].whatMove == moveType::PromotionCapture) {
				possibleMoves[i].promotion = theMove.promotion;
			}
			prevMoveIsCheck = isCheckMove(possibleMoves[i]);
			makeTempMove(possibleMoves[i]);
			moveStack.push_back(lastMove);
			moveHistory.push_back(possibleMoves[i]);
			if (currentColour == Colour::White) {
				currentColour = Colour::Black;
			}
			else if (currentColour == Colour::Black) {
				currentColour = Colour::White;
			}
			updatePM();
			//printPossibleMoves();
			updateTD();
			return;
		}
	}
	throw(std::invalid_argument("ERROR"));
}

void chessBoard::resign() {
	if (inGame == true) {
		if (currentColour == Colour::Black) {
			whitescore = whitescore + 1;
		}
		else if (currentColour == Colour::White) {
			blackscore = blackscore + 1;
		}
		inGame = false;
		init();
	}
	else {
		cout << "There is no game running." << endl;
	}
}

void chessBoard::checkmate() {
	if (currentColour == Colour::Black) {
		whitescore = whitescore + 1;
	}
	else if (currentColour == Colour::White) {
		blackscore = blackscore + 1;
	}
	inGame = false;
	init();
}

void chessBoard::stalemate() {
	whitescore = whitescore + 0.5;
	blackscore = blackscore + 0.5;
	inGame = false;
	init();
}

bool chessBoard::inCheck() {
	return prevMoveIsCheck;
}

bool chessBoard::getSetup() {
	return setupMode;
}

void chessBoard::gameStart() {
	inGame = true;
}

void chessBoard::init() {
	if (td != nullptr) {
		delete td;
	}
	if (gd != nullptr) {
		delete gd;
	}
	for (int i = 0; i < gameBoard.size(); ++i) {
		for (int j = 0; j < gameBoard[i].size(); ++j) {
			delete gameBoard[i][j];
		}
	}
	for (int i = 0; i < moveStack.size(); ++i) {
		for (int j = 0; j < moveStack[i].size(); ++j) {
			delete moveStack[i][j].second;
		}
	}
	moveHistory.clear();
	lastMove.clear();
	moveStack.clear();
	possibleMoves.clear();
	gameBoard.clear();
	gd = new GraphicsDisplay(2);
	td = new TextDisplay(2);

	for (int i = 0; i < 12; i++) {
		vector<Cell*> row;
		for (int j = 0; j < 12; j++) {
			if (i < 2 || j < 2 || i > 9 || j > 9) {
				NULLCell *n = new NULLCell(i, j, Colour::NoColour, gameBoard, moveHistory);
				row.push_back(n);
			}
			else {
				Empty *e = new Empty(i, j, Colour::NoColour, gameBoard, moveHistory);
				row.push_back(e);
			}
		}
		gameBoard.push_back(row);
	}
	setupMode = true;
	set('a', 1, 'R');
	set('b', 1, 'N');
	set('c', 1, 'B');
	set('d', 1, 'Q');
	set('e', 1, 'K');
	set('f', 1, 'B');
	set('g', 1, 'N');
	set('h', 1, 'R');
	set('a', 2, 'P');
	set('b', 2, 'P');
	set('c', 2, 'P');
	set('d', 2, 'P');
	set('e', 2, 'P');
	set('f', 2, 'P');
	set('g', 2, 'P');
	set('h', 2, 'P');
	set('a', 8, 'r');
	set('b', 8, 'n');
	set('c', 8, 'b');
	set('d', 8, 'q');
	set('e', 8, 'k');
	set('f', 8, 'b');
	set('g', 8, 'n');
	set('h', 8, 'r');
	set('a', 7, 'p');
	set('b', 7, 'p');
	set('c', 7, 'p');
	set('d', 7, 'p');
	set('e', 7, 'p');
	set('f', 7, 'p');
	set('g', 7, 'p');
	set('h', 7, 'p');
	setupMode = false;
	updateTD();
}

void chessBoard::printHistory() {
	for (int i = (moveHistory.size() - 1); i >= 0; --i) {
		char outchar = 'a' + moveHistory[i].startPosition.second - 2;
		cout << outchar << 10 - moveHistory[i].startPosition.first << " ";
		outchar = 'a' + moveHistory[i].endPosition.second - 2;
		cout << outchar << 10 - moveHistory[i].endPosition.first << endl;
	}
}

chessBoard::~chessBoard() {
	if (gd != nullptr) {
		delete gd;
	}
	if (td != nullptr) {
		delete td;
	}
	for (int i = 0; i < gameBoard.size(); ++i) {
		for (int j = 0; j < gameBoard[i].size(); ++j) {
			delete gameBoard[i][j];
		}
	}
	for (int i = 0; i < moveStack.size(); ++i) {
		for (int j = 0; j < moveStack[i].size(); ++j) {
			delete moveStack[i][j].second;
		}
	}
}

void chessBoard::toSetup() {
	if (inGame != true) {
		setupMode = true;
	}
	else {
		cout << "The game is running!" << endl;
	}
}

void chessBoard::toGame() {
	int wKing = 0;
	int bKing = 0;
	bool wrongPawn = false;
	for (int r = 2; r < 10; r++) {
		for (int c = 2; c < 10; c++) {
			Piece piece = gameBoard.at(r).at(c)->getInfo().piece;
			Colour cl = gameBoard.at(r).at(c)->getInfo().colour;
			if (piece == Piece::Pawn) {
				if (r == 2 || r == 9) wrongPawn = true;
			}
			if (piece == Piece::King) {
				if (cl == Colour::White) {
					wKing++;
				}
				else if (cl == Colour::Black) {
					bKing++;
				}
			}
		}
	}

	if (wrongPawn) {
		cout << "There are pawns in incorrect rows." << endl;
	}
	else if (wKing != 1 || bKing != 1) {
		cout << "King's number is wrong!" << endl;
	}
	else {
		updatePM();
		if (isStalemate()) {
			std::cout << "The game will begin at a stalemate, which is not allowed.";
		}
		else {
			setupMode = false;
			updateTD();
		}
	}
}

void chessBoard::set(char col, int row, char piece) {
	if (setupMode) {
		int c = col - 'a' + 2;
		int r = 8 - row + 2;
		delete gameBoard.at(r).at(c);
		if (piece == 'p') {
			gameBoard.at(r).at(c) = new Pawn(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'P') {
			gameBoard.at(r).at(c) = new Pawn(r, c, Colour::White, gameBoard, moveHistory);
		}
		else if (piece == 'n') {
			gameBoard.at(r).at(c) = new Knight(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'N') {
			gameBoard.at(r).at(c) = new Knight(r, c, Colour::White, gameBoard, moveHistory);
		}
		else if (piece == 'b') {
			gameBoard.at(r).at(c) = new Bishop(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'B') {
			gameBoard.at(r).at(c) = new Bishop(r, c, Colour::White, gameBoard, moveHistory);
		}
		else if (piece == 'r') {
			gameBoard.at(r).at(c) = new Rook(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'R') {
			gameBoard.at(r).at(c) = new Rook(r, c, Colour::White, gameBoard, moveHistory);
		}
		else if (piece == 'q') {
			gameBoard.at(r).at(c) = new Queen(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'Q') {
			gameBoard.at(r).at(c) = new Queen(r, c, Colour::White, gameBoard, moveHistory);
		}
		else if (piece == 'k') {
			gameBoard.at(r).at(c) = new King(r, c, Colour::Black, gameBoard, moveHistory);
		}
		else if (piece == 'K') {
			gameBoard.at(r).at(c) = new King(r, c, Colour::White, gameBoard, moveHistory);
		}
	}
}

void chessBoard::unset(char col, int row) {
	if (setupMode) {
		int c = col - 'a' + 2;
		int r = 8 - row + 2;
		delete gameBoard.at(r).at(c);
		Empty *e = new Empty(r, c, Colour::NoColour, gameBoard, moveHistory);
		gameBoard.at(r).at(c) = e;
	}
}

void chessBoard::setColour(Colour c) {
	if (setupMode) {
		currentColour = c;
	}
}

void chessBoard::updateTD() {
	for (int i = 2; i < 10; i++) {
		for (int j = 2; j < 10; j++) {
			td->notify(gameBoard.at(i).at(j));
			gd->notify(gameBoard.at(i).at(j));
		}
	}
}

Colour chessBoard::getColour() {
	return currentColour;
}

void chessBoard::printScore() {
	cout << "Final Score:" << endl;
	cout << "White: " << whitescore << endl;
	cout << "Black: " << blackscore << endl;
}

ostream &operator<<(ostream &out, const chessBoard &cb) { // print
	return out << *(cb.td);
}
