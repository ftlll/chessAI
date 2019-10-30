#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <stdexcept>
#include <vector>
#include "info.h"
#include "move.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class chessBoard {
	std::vector<std::vector<Cell*>> gameBoard;
	std::vector<std::pair<std::pair<int, int>, Cell*>> lastMove;
	std::vector<std::vector<std::pair<std::pair<int, int>, Cell*>>> moveStack;
	TextDisplay *td = nullptr;
	GraphicsDisplay *gd = nullptr;
	double whitescore = 0;
	double blackscore = 0;
	bool setupMode = false;
	bool inGame = false;
	std::vector<chessMove> moveHistory;
	std::vector<chessMove> possibleMoves;
	Colour currentColour = Colour::White;
	std::vector<chessMove> getColourNextMove(Colour requiredColour);
	bool validateMove(std::vector<chessMove> futureMoves);
	bool isAvoidCaptureMove(std::vector<chessMove>& futureMoves);
	int getMaxDrawback(std::vector<chessMove> futureMoves);
	bool prevMoveIsCheck = false;
	void makeTempMove(chessMove theMove);
	void undoTempMove();
	int getPieceValue(Piece thePiece);

public:
	void updatePM();
	void printPossibleMoves();
	void makeMove(chessMove theMove);
	std::vector<chessMove> getPossibleMoves();
	std::vector<chessMove> getAvoidCaptureMoves();
	std::vector<chessMove> getPositiveMoves();
	bool isStalemate();
	bool isCheckmate();
	bool isCheckMove(chessMove theMove);
	bool inCheck();
	void resign();
	void init();
	void stalemate();
	void checkmate();
	void printHistory();
	void undoMove();

	~chessBoard();
	bool getSetup();
	void gameStart();
	void toSetup();
	void toGame();
	void set(char col, int row, char piece);
	void unset(char col, int row);
	void setColour(Colour c);
	Colour getColour();
	void updateTD();
	void printScore();
	friend std::ostream &operator<<(std::ostream &out, const chessBoard &cb);
};
#endif
