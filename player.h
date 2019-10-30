#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"

class Player: public Strategy {

public:
	Player(chessBoard& theBoard);
	chessMove getNextMove() override;
};

#endif
