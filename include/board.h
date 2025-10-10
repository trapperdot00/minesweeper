#ifndef BOARD_H
#define BOARD_H

#include "point.h"

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename tile>
class board {
public:
	size_t size() const;
	size_t width() const;
	size_t height() const;

	bool set_tile(point, tile);
	tile get_tile(point) const;
protected:
	board(size_t width, size_t height, tile init);

	bool is_in_range(point) const;
	void throw_if_not_in_range(point) const;
private:
	size_t width_;
	size_t height_;
	std::vector<std::vector<tile>> data;
};

#include "board.tpp"

#endif
