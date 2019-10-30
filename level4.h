#ifndef LEVEL4_H
#define LEVEL4_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"

class Level4 : public Strategy {

public:
	Level4(chessBoard& theBoard);
	chessMove getNextMove() override;
};

#endif
