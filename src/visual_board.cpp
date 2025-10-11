#include "visual_board.h"

#include <iostream>

visual_board::visual_board(const mine_board& mb) :
	board{mb.width(), mb.height(), visual_tile{}},
	clicked_count_{0},
	flagged_count_{0},
	mb_{mb}
{
	update_neighbor_counts();
}

void visual_board::reset() {
	board::reset(visual_tile{});
	clicked_count_ = 0;
	flagged_count_ = 0;
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
	++clicked_count_;
	return true;
}

bool visual_board::toggle_flag(point p) {
	visual_tile vt = get_tile(p);
	switch (vt.state) {
	case visual_tile::clickable:
		vt.state = visual_tile::flagged;
		++flagged_count_;
		break;
	case visual_tile::flagged:
		vt.state = visual_tile::clickable;
		--flagged_count_;
		break;
	default:
		return false;
		break;
	}
	set_tile(p, vt);
	return true;
}

size_t visual_board::clickable_count() const {
	return size() - clicked_count() - flagged_count();
}

size_t visual_board::clicked_count() const {
	return clicked_count_;
}

size_t visual_board::flagged_count() const {
	return flagged_count_;
}
