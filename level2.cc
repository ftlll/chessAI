#include <vector>
#include <random>
#include <chrono> 
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"
#include "level2.h"

Level2::Level2(chessBoard& theBoard) : Strategy(theBoard) {}

chessMove Level2::getNextMove() {
	std::vector<chessMove> possibleMoves = theBoard.getPossibleMoves();
	std::vector<chessMove> captureMoves;
	for (int i = 0; i < possibleMoves.size(); ++i) {
		if (possibleMoves[i].whatMove == moveType::Capture or possibleMoves[i].whatMove == moveType::PromotionCapture or theBoard.isCheckMove(possibleMoves[i])) {
			captureMoves.push_back(possibleMoves[i]);
		}
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	if (captureMoves.size() != 0) {
		std::uniform_int_distribution<> myRand(0, captureMoves.size() - 1);
		return captureMoves[myRand(gen)];
	}
	else {
		std::uniform_int_distribution<> myRand(0, possibleMoves.size() - 1);
		return possibleMoves[myRand(gen)];
	}
}
