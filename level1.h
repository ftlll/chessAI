#ifndef LEVEL1_H
#define LEVEL1_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"

class Level1 : public Strategy {

public:
	Level1(chessBoard& theBoard);
	chessMove getNextMove() override;
};

#endif
