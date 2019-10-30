#ifndef LEVEL3_H
#define LEVEL3_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"

class Level3 : public Strategy {

public:
	Level3(chessBoard& theBoard);
	chessMove getNextMove() override;
};

#endif
