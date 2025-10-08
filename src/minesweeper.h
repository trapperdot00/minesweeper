#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "board.h"

#include <cstddef>

class minesweeper {
public:
	minesweeper(size_t width, size_t height, size_t mine_count);
	board& get() { return b; }
private:
	void put_mines(size_t count);
	board b;
};

#endif
