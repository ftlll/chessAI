#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "info.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int player) {
	if (player == 2) {
		for (int i = 0; i < 8; i++) {
			vector<char> c;
			for (int j = 0; j < 8; j++) {
				if ((i + j) % 2 == 0) {
					c.push_back(' ');
				}
				else {
					c.push_back('_');
				}
			}
			theDisplay.push_back(c);
		}
	}
}

void TextDisplay::notify(Cell *whoNotified) {
	int row = whoNotified->getInfo().row - 2;
	int col = whoNotified->getInfo().col - 2;
	Colour cl = whoNotified->getInfo().colour;
	Piece pi = whoNotified->getInfo().piece;
	if (cl == Colour::NoColour or whoNotified->getInfo().isPiece == false) {
		if ((row + col) % 2 == 0) {
			theDisplay.at(row).at(col) = ' ';
		}
		else {
			theDisplay.at(row).at(col) = '_';
		}
	}
	else if (cl == Colour::White) {
		if (pi == Piece::Pawn) {
			theDisplay.at(row).at(col) = 'P';
		}
		else if (pi == Piece::Bishop) {
			theDisplay.at(row).at(col) = 'B';
		}
		else if (pi == Piece::Knight) {
			theDisplay.at(row).at(col) = 'N';
		}
		else if (pi == Piece::Rook) {
			theDisplay.at(row).at(col) = 'R';
		}
		else if (pi == Piece::Queen) {
			theDisplay.at(row).at(col) = 'Q';
		}
		else if (pi == Piece::King) {
			theDisplay.at(row).at(col) = 'K';
		}
	}
	else if (cl == Colour::Black) {
		if (pi == Piece::Pawn) {
			theDisplay.at(row).at(col) = 'p';
		}
		else if (pi == Piece::Bishop) {
			theDisplay.at(row).at(col) = 'b';
		}
		else if (pi == Piece::Knight) {
			theDisplay.at(row).at(col) = 'n';
		}
		else if (pi == Piece::Rook) {
			theDisplay.at(row).at(col) = 'r';
		}
		else if (pi == Piece::Queen) {
			theDisplay.at(row).at(col) = 'q';
		}
		else if (pi == Piece::King) {
			theDisplay.at(row).at(col) = 'k';
		}
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) { // output the textdisplay
	for (int i = 0; i < 8; i++) {
		out << 8 - i << " ";
		for (int j = 0; j < 8; j++) {
			out << td.theDisplay.at(i).at(j);
		}
		out << endl;
	}
	out << "  abcdefgh";
	return out;
}
