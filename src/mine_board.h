#ifndef MINE_BOARD_H
#define MINE_BOARD_H

#include "board.h"
#include "mine_tile.h"

class mine_board : public board<mine_tile> {
public:
	using board::board;

	void put_mine(point);
	void erase_mine(point);

	bool has_mine(point) const;
	int neighboring_mines(point) const;

	size_t mine_count() const;

	void debug_print() const;
private:
	size_t mine_count_ = 0;
};

#endif
