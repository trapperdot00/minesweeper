#ifndef BOARD_H
#define BOARD_H

#include "point.h"
#include "field.h"

#include <cstddef>
#include <vector>

class board {
public:
	board(size_t width, size_t height);

	void put_mine(point);
	void erase_mine(point);

	bool has_mine(point) const;
	int neighboring_mines(point) const;

	size_t width() const;
	size_t height() const;

	void debug_print() const;
private:
	void set_field(point, field);
	field get_field(point) const;

	bool is_in_range(point) const;
	void throw_if_not_in_range(point) const;

	size_t width_;
	size_t height_;
	std::vector<std::vector<field>> data;
};

#endif
