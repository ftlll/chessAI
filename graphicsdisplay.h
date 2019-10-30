#ifndef _GRAPHICSDISPLAY_
#define _GRAPHICSDISPLAY_
#include <iostream>
#include <vector>
#include <string>
#include <X11/Xlib.h>
#include "window.h"
#include "info.h"
#include "cell.h"
class Cell;

class GraphicsDisplay{
  const int player;
  Xwindow xw;

 public:
  GraphicsDisplay(int player);

  void notify(Cell *whoNotified);

  void fillRectangle(int x, int y, int colour);

  void drawString(int x, int y,std::string msg, int colour);
};
#endif
