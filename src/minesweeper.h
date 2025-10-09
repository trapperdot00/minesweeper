#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mine_board.h"

#include <cstddef>

class minesweeper {
public:
	minesweeper(size_t width, size_t height, size_t mine_count);
	mine_board& get() { return mb; }
private:
	void put_mines(size_t count);

	mine_board mb;
};

#endif
