#ifndef LEVEL2_H
#define LEVEL2_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"

class Level2 : public Strategy {

public:
	Level2(chessBoard& theBoard);
	chessMove getNextMove() override;
};

#endif
