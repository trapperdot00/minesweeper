#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mine_board.h"
#include "visual_board.h"
#include "cursor.h"

#include <cstddef>
#include <iostream>

class minesweeper {
public:
	minesweeper(size_t width, size_t height, size_t mine_count);

	void play();

	void halo(point p) {
		std::cout << p << " halo\n";
	}
private:
	void put_mines(size_t count);

	mine_board mb;
	visual_board vb;
	cursor pos;
};

#endif
