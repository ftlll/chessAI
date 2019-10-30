#include <iostream>
#include <vector>
#include <string>
#include <X11/Xlib.h>
#include "window.h"
#include "info.h"
#include "graphicsdisplay.h"
#include "cell.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int player):player{player}{
    if(player == 2){
        for(int c = 0; c < 8;c++){
            string col = to_string(8 - c);
            drawString( 15, c * 50 + 25, col, 4);
            for(int r = 0; r < 8; r++){
                if( (c + r)% 2 == 0){
                    fillRectangle(c,r,0);
                }else{
                    fillRectangle(c,r,1);
                }
            }
        }
        drawString(75, 425, "a", 4);
        drawString(125, 425, "b", 4);
        drawString(175, 425, "c", 4);
        drawString(225, 425, "d", 4);
        drawString(275, 425, "e", 4);
        drawString(325, 425, "f", 4);
        drawString(375, 425, "g", 4);
        drawString(425, 425, "h", 4);
    }
}

void GraphicsDisplay::notify(Cell *whoNotified){
    int row = whoNotified->getInfo().row - 2;
    int col = whoNotified->getInfo().col - 2;
    int xPos = col * 50 + 75;
    int yPos = row * 50 + 25;
    Colour cl = whoNotified->getInfo().colour;
    Piece pi = whoNotified->getInfo().piece;
    if( (col + row)% 2 == 0){
       fillRectangle(col,row,0);
    }else{
       fillRectangle(col,row,1);
    }
    if (cl == Colour::White && whoNotified->getInfo().isPiece == true) {
		if (pi == Piece::Pawn) {
			drawString(xPos,yPos,"P",4);
		}
		else if (pi == Piece::Bishop) {
			drawString(xPos,yPos,"B",4);
		}
		else if (pi == Piece::Knight) {
			drawString(xPos,yPos,"N",4);
		}
		else if (pi == Piece::Rook) {
			drawString(xPos,yPos,"R",4);
		}
		else if (pi == Piece::Queen) {
			drawString(xPos,yPos,"Q",4);
		}
		else if (pi == Piece::King) {
			drawString(xPos,yPos,"K",4);
		}
	}
	else if (cl == Colour::Black && whoNotified->getInfo().isPiece == true) {
		if (pi == Piece::Pawn) {
			drawString(xPos,yPos,"p",4);
		}
		else if (pi == Piece::Bishop) {
			drawString(xPos,yPos,"b",4);
		}
		else if (pi == Piece::Knight) {
			drawString(xPos,yPos,"n",4);
		}
		else if (pi == Piece::Rook) {
			drawString(xPos,yPos,"r",4);
		}
		else if (pi == Piece::Queen) {
			drawString(xPos,yPos,"q",4);
		}
		else if (pi == Piece::King) {
			drawString(xPos,yPos,"k",4);
		}
	}
}

void GraphicsDisplay::fillRectangle(int x, int y, int colour){  // to draw a square foe each one
    if(player == 2){
        int width = 50;
        if(colour == 1){
            xw.fillRectangle(x*width + 50,y*width,width,width);
        }else if(colour == 0){
            xw.fillRectangle(x*width + 50,y*width,width,width, 0);
        }
    }
}

void GraphicsDisplay::drawString(int x, int y, string msg,int colour){
    xw.drawString(x,y,msg,colour);
}
