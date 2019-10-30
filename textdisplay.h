#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
class Cell;

class TextDisplay {
	std::vector<std::vector<char>> theDisplay;

public:
	TextDisplay(int player);

	void notify(Cell *whoNotified);

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
