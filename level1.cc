#include <vector>
#include <random>
#include <chrono> 
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"
#include "level1.h"

Level1::Level1(chessBoard& theBoard) : Strategy(theBoard) {}

chessMove Level1::getNextMove() {
	std::vector<chessMove> possibleMoves = theBoard.getPossibleMoves();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> myRand(0, possibleMoves.size() - 1);
	return possibleMoves[myRand(gen)];
}
