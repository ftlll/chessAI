#include <vector>
#include <random>
#include <chrono> 
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"
#include "level3.h"

Level3::Level3(chessBoard& theBoard) : Strategy(theBoard) {}

chessMove Level3::getNextMove() {
	std::vector<chessMove> possibleMoves = theBoard.getPossibleMoves();
	std::vector<chessMove> captureMoves;
	std::vector<chessMove> avoidDangerMoves = theBoard.getAvoidCaptureMoves();
	std::vector<chessMove> avoidDangerCaptureMoves;

	for (int i = 0; i < possibleMoves.size(); ++i) {
		if (possibleMoves[i].whatMove == moveType::Capture or possibleMoves[i].whatMove == moveType::PromotionCapture or theBoard.isCheckMove(possibleMoves[i])) {
			captureMoves.push_back(possibleMoves[i]);
		}
	}
	
	for (int i = 0; i < avoidDangerMoves.size(); ++i) {
		if (avoidDangerMoves[i].whatMove == moveType::Capture or possibleMoves[i].whatMove == moveType::PromotionCapture or theBoard.isCheckMove(possibleMoves[i])) {
			avoidDangerCaptureMoves.push_back(avoidDangerMoves[i]);
		}
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	if (avoidDangerCaptureMoves.size() != 0) {
		std::uniform_int_distribution<> myRand(0, avoidDangerCaptureMoves.size() - 1);
		return avoidDangerCaptureMoves[myRand(gen)];
	}
	else if (avoidDangerMoves.size() != 0) {
		std::uniform_int_distribution<> myRand(0, avoidDangerMoves.size() - 1);
		return avoidDangerMoves[myRand(gen)];
	}
	else if (captureMoves.size() != 0) {
		std::uniform_int_distribution<> myRand(0, captureMoves.size() - 1);
		return captureMoves[myRand(gen)];
	}
	else {
		std::uniform_int_distribution<> myRand(0, possibleMoves.size() - 1);
		return possibleMoves[myRand(gen)];
	}
}
