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

bool visual_board::click(point p) {
	visual_tile vt = get_tile(p);
	if (vt.state != visual_tile::clickable) {
		return false;
	}
	vt.state = visual_tile::clicked;
	set_tile(p, vt);
	return true;
}

bool visual_board::toggle_flag(point p) {
	visual_tile vt = get_tile(p);
	switch (vt.state) {
	case visual_tile::clickable:
		vt.state = visual_tile::flagged;
		break;
	case visual_tile::flagged:
		vt.state = visual_tile::clickable;
		break;
	default:
		return false;
		break;
	}
	set_tile(p, vt);
	return true;
}

size_t visual_board::clicked_count() const {
	size_t clicked = 0;
	for (size_t y = 0; y < height(); ++y) {
		for (size_t x = 0; x < width(); ++x) {
			point p{x, y};
			visual_tile vt = get_tile(p);
			if (vt.state == visual_tile::clicked) {
				++clicked;
			}
		}
	}
	return clicked;
}
