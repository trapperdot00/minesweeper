#include "mine_board.h"

#include <iostream>

mine_board::mine_board(size_t width, size_t height) :
	board{width, height, mine_tile::empty}
{}

void mine_board::reset() {
	board::reset(mine_tile::empty);
	mine_count_ = 0;
}

void mine_board::put_mine(point p) {
	if (set_tile(p, mine_tile::mine)) {
		++mine_count_;
	}
}

void mine_board::erase_mine(point p) {
	if (set_tile(p, mine_tile::empty)) {
		--mine_count_;
	}
}

bool mine_board::has_mine(point p) const {
	return get_tile(p) == mine_tile::mine;
}

int mine_board::neighboring_mines(point p) const {
	throw_if_not_in_range(p);
	int result = 0;	
	for_each_neighbor_pos(p, [this, p, &result](point neighbor) {
		if (neighbor != p && has_mine(neighbor)) {
			++result;
		}
	});
	return result;
}

size_t mine_board::mine_count() const {
	return mine_count_;
}

size_t mine_board::empty_count() const {
	return size() - mine_count();
}
