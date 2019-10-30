#include<vector>
#include<string>
#include<stdexcept>
#include "chessboard.h"
#include "info.h"
#include "move.h"
#include "strategy.h"
#include "player.h"
using namespace std;

Player::Player(chessBoard& theBoard) : Strategy(theBoard) {}

chessMove Player::getNextMove() {
	char startC;
	int startR;
	char endC;
	int endR;
	char pro;
	if (cin >> startC >> startR >> endC >> endR) {
		std::pair<int, int> startPos(10 - startR, startC - 'a' + 2);
		std::pair<int, int> endPos(10 - endR, endC - 'a' + 2);
		std::vector<chessMove> possibleMoves = theBoard.getPossibleMoves();
		for (int i = 0; i < possibleMoves.size(); i++) {
			if (possibleMoves.at(i).startPosition == startPos and possibleMoves.at(i).endPosition == endPos) {
				if (possibleMoves.at(i).whatMove == moveType::PromotionMove or possibleMoves.at(i).whatMove == moveType::PromotionCapture) {
					if (cin >> pro) {}
					else {
						throw(std::invalid_argument("ERROR"));
					}
					chessMove returnMove = possibleMoves.at(i);
					if (pro == 'r' || pro == 'R') {
						returnMove.promotion = Piece::Rook;
					}
					else if (pro == 'n' || pro == 'N') {
						returnMove.promotion = Piece::Knight;
					}
					else if (pro == 'Q' || pro == 'q') {
						returnMove.promotion = Piece::Queen;
					}
					else if (pro == 'b' || pro == 'B') {
						returnMove.promotion = Piece::Bishop;
					}
					else {
						throw(std::invalid_argument("ERROR"));
					}
					return returnMove;
				}
				else {
					return possibleMoves.at(i);
				}
			}
		}
		throw(std::invalid_argument("ERROR"));
	}
	else {
		throw(std::invalid_argument("ERROR"));
	}
}
