#include <iostream>
#include <string>
#include "chessboard.h"
#include "strategy.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "player.h"
#include "graphicsdisplay.h"
using namespace std;

int main() {
	chessBoard cb;
	string cmd;
	//chessboard and command
	cb.init();
	cout << cb << endl;
	//cb.updatePM();
	//cb.printPossibleMoves();
	//cb.printPossibleMoves();
	Strategy* WhitePlayer = nullptr;
	Strategy* BlackPlayer = nullptr;
	try {
		while (cin >> cmd) {
			if (cmd == "game") {
				if (cb.getSetup() == false) {
					bool invalidOption = false;
					string wplayer;
					string bplayer;
					cin >> wplayer >> bplayer;
					if (WhitePlayer != nullptr) {
						delete WhitePlayer;
						WhitePlayer = nullptr;
					}
					if (BlackPlayer != nullptr) {
						delete BlackPlayer;
						WhitePlayer = nullptr;
					}

					if (wplayer == "human") {
						WhitePlayer = new Player(cb);
					}
					else if (wplayer == "computer[1]") {
						WhitePlayer = new Level1(cb);
					}
					else if (wplayer == "computer[2]") {
						WhitePlayer = new Level2(cb);
					}
					else if (wplayer == "computer[3]") {
						WhitePlayer = new Level3(cb);
					}
					else if (wplayer == "computer[4]") {
						WhitePlayer = new Level4(cb);
					}
					else {
						std::cout << "INVALID OPTION" << std::endl;
						invalidOption = true;
					}

					if (bplayer == "human") {
						BlackPlayer = new Player(cb);
					}
					else if (bplayer == "computer[1]") {
						BlackPlayer = new Level1(cb);
					}
					else if (bplayer == "computer[2]") {
						BlackPlayer = new Level2(cb);
					}
					else if (bplayer == "computer[3]") {
						BlackPlayer = new Level3(cb);
					}
					else if (bplayer == "computer[4]") {
						BlackPlayer = new Level4(cb);
					}
					else {
						std::cout << "INVALID OPTION" << std::endl;
						invalidOption = true;
					}
					if (invalidOption) {
						if (WhitePlayer != nullptr) {
							delete WhitePlayer;
							WhitePlayer = nullptr;
						}
						if (BlackPlayer != nullptr) {
							delete BlackPlayer;
							WhitePlayer = nullptr;
						}
					}
					else {
						cb.gameStart();
						cb.updatePM();
						cout << cb << endl;
					}
				}
				else {
					std::cout << "Currently in setup mode" << std::endl;
				}
			}
			else if (cmd == "move") {
				try {
					if (cb.getColour() == Colour::White) {
						cb.makeMove(WhitePlayer->getNextMove());
					}
					else if (cb.getColour() == Colour::Black) {
						cb.makeMove(BlackPlayer->getNextMove());
					}
				}
				catch (const std::invalid_argument& prevError) { 
					std::cout << "Invalid Move" << std::endl;
				}

				if (cb.inCheck()) {
					if (cb.getColour() == Colour::White) {
						std::cout << "White is in check." << std::endl;
					}
					else if (cb.getColour() == Colour::Black) {
						std::cout << "Black is in check." << std::endl;
					}
				}

				if (cb.isCheckmate()) {
					if (cb.getColour() == Colour::White) {
						std::cout << "Checkmate! Black wins!" << std::endl;
					}
					else if (cb.getColour() == Colour::Black) {
						std::cout << "Checkmate! White wins!" << std::endl;
					}
					cb.checkmate();
				}
				else if (cb.isStalemate()) {
					std::cout << "Stalemate!" << std::endl;
					cb.stalemate();
				}
				cout << cb << endl;
			}
			else if (cmd == "resign") {
				if (cb.getColour() == Colour::White) {
					std::cout << "Black wins!" << std::endl;
				}
				else if (cb.getColour() == Colour::Black) {
					std::cout << "White wins!" << std::endl;
				}
				cb.resign();
			}
			else if (cmd == "setup") {
				cb.toSetup();
			}
			else if (cmd == "history") {
				cb.printHistory();
			}
			else if (cmd == "undo") {
				cb.undoMove();
				cout << cb << endl;
			}
			else if (cmd == "+") {
				char p;
				char col;
				int row;
				cin >> p >> col >> row;
				cb.set(col, row, p);
				cb.updateTD();
				cout << cb << endl;
			}
			else if (cmd == "-") {
				char col;
				int row;
				cin >> col >> row;
				cb.unset(col, row);
				cb.updateTD();
				cout << cb << endl;
			}
			else if (cmd == "=") {
				string colour;
				cin >> colour;
				if (colour == "White") {
					cb.setColour(Colour::White);
				}
				else if (colour == "Black") {
					cb.setColour(Colour::Black);
				}
				else {
					std::cout << "Not a valid colour" << std::endl;
				}
			}
			else if (cmd == "done") {
				cb.toGame();
			}
			else {
				std::cout << "Invalid command" << std::endl;
			}
		}
	}
	catch (ios::failure &) {}  // Any I/O failure quits
	cb.printScore();
	if (WhitePlayer != nullptr) {
		delete WhitePlayer;
	}
	if (BlackPlayer != nullptr) {
		delete BlackPlayer;
	}
}
