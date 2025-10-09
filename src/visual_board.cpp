#include "visual_board.h"

#include <iostream>

visual_board::visual_board(const mine_board& mb) :
	board{mb.width(), mb.height(), visual_tile{}},
	mb_{mb}
{
	update_neighbor_counts();
}

void visual_board::update_neighbor_counts() {
	for (size_t y = 0; y < height(); ++y) {
		for (size_t x = 0; x < width(); ++x) {
			point p{x, y};
			visual_tile vt = get_tile(p);
			vt.neighbor_count = mb_.neighboring_mines(p);
			set_tile(p, vt);
		}
	}
}

void visual_board::click(point p) {
	visual_tile vt = get_tile(p);
	vt.state = visual_tile::clicked;
	set_tile(p, vt);
}

void visual_board::debug_print() const {
	for (size_t y = 0; y < height(); ++y) {
		for (size_t x = 0; x < width(); ++x) {
			point p{x, y};
			visual_tile vt = get_tile(p);
			if (vt.state == visual_tile::clicked) {
				std::cout << vt.neighbor_count;
			} else {
				std::cout << "?";
			}
		}
		std::cout << '\n';
	}
}
