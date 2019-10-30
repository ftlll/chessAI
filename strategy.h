#ifndef STRATEGY_H
#define STRATEGY_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"

class Strategy {
protected:
	chessBoard& theBoard;
public:
	Strategy(chessBoard& theBoard);
	virtual chessMove getNextMove() = 0;
};

#endif
