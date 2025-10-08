#include "board.h"

#include <iostream>

board::board(size_t width, size_t height) :
	data(height, std::vector<field>(width))
{}

bool board::has_mine(size_t x, size_t y) const {
	return data[x][y] == field::mine;
}

void board::debug_print() const {
	for (size_t y = 0; y < data.size(); ++y) {
		for (size_t x = 0; x < data[y].size(); ++x) {
			std::cout << (data[y][x] == field::empty ? "O" : "*");
		}
		std::cout << '\n';
	}
}
