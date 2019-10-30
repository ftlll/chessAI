#include <vector>
#include <random>
#include <chrono> 
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"
#include "level4.h"

Level4::Level4(chessBoard& theBoard) : Strategy(theBoard) {}

chessMove Level4::getNextMove() {
	std::vector<chessMove> goodMoves = theBoard.getPositiveMoves();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> myRand(0, goodMoves.size() - 1);
	return goodMoves[myRand(gen)];
}
