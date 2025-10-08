#include "board.h"

#include <stdexcept>
#include <iostream>

board::board(size_t width, size_t height) :
	width_{width},
	height_{height},
	data(height, std::vector<field>(width))
{
	if (width == 0 || height == 0) {
		throw std::invalid_argument{"board size must not be 0"};
	}
}

void board::put_mine(point p) {
	set_field(p, field::mine);
}

void board::erase_mine(point p) {
	set_field(p, field::empty);
}

bool board::has_mine(point p) const {
	return data[p.y][p.x] == field::mine;
}

size_t board::width() const {
	return width_;
}

size_t board::height() const {
	return height_;
}

void board::debug_print() const {
	for (size_t y = 0; y < data.size(); ++y) {
		for (size_t x = 0; x < data[y].size(); ++x) {
			std::cout << (data[y][x] == field::empty ? "O" : "*");
		}
		std::cout << '\n';
	}
}

bool board::is_in_range(point p) const {
	return p.x < width_ && p.y < height_;
}

void board::throw_if_not_in_range(point p) const {
	if (!is_in_range(p)) {
		throw std::out_of_range{"Point out-of-range"};
	}
}

void board::set_field(point p, field f) {
	throw_if_not_in_range(p);
	data[p.y][p.x] = f;
}
