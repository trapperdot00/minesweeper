#ifndef BOARD_H
#define BOARD_H

#include "field.h"

#include <cstddef>
#include <vector>

class board {
public:
	board(size_t width, size_t height);

	bool has_mine(size_t x, size_t y) const;

	void debug_print() const;
private:
	std::vector<std::vector<field>> data;
};

#endif
