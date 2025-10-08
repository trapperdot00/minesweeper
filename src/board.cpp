#include "board.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

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
	return get_field(p) == field::mine;
}

int board::neighboring_mines(point p) const {
	throw_if_not_in_range(p);
	int result = 0;	
	const size_t start_y = std::min(p.y - 1, p.y);
	const size_t end_y = std::min(p.y + 1, height_ - 1);
	for (size_t y = start_y; y <= end_y; ++y) {
		const size_t start_x = std::min(p.x - 1, p.x);
		const size_t end_x = std::min(p.x + 1, width_ - 1);
		for (size_t x = start_x; x <= end_x; ++x) {
			point neighbor{x, y};
			if (neighbor != p && has_mine(neighbor)) {
				++result;
			}
		}
	}
	return result;
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

field board::get_field(point p) const {
	throw_if_not_in_range(p);
	return data[p.y][p.x];
}
