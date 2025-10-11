#include "visual_board.h"

#include <iostream>
#include <algorithm>

visual_board::visual_board(const mine_board& mb) :
	board{mb.width(), mb.height(), visual_tile{}},
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
	for_each_pos([this](point p) {
		visual_tile vt = get_tile(p);
		vt.neighbor_count = mb_.neighboring_mines(p);
		set_tile(p, vt);
	});
}

bool visual_board::click(point p) {
	visual_tile vt = get_tile(p);
	if (vt.state != visual_tile::clickable) {
		return false;
	}
	clear_tile(p);
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
	return size() - clicked_count_ - flagged_count_;
}

size_t visual_board::clicked_count() const {
	return clicked_count_;
}

size_t visual_board::flagged_count() const {
	return flagged_count_;
}

void visual_board::clear_tile(point p, point* parent) {
	visual_tile vt = get_tile(p);
	if (parent && (mb_.has_mine(p) || vt.state != visual_tile::clickable))
	{
		return;
	}
	vt.state = visual_tile::clicked;
	set_tile(p, vt);
	++clicked_count_;
	if (vt.neighbor_count) {
		return;
	}
	for_each_orthogonal_neighbor_pos(p, [this, &p](point neighbor) {
		clear_tile(neighbor, &p);
	});
	for_each_diagonal_neighbor_pos(p, [this, &p](point neighbor) {
		clear_tile(neighbor, &p);
	});
}

int visual_board::flagged_neighbors_count(point p) const {
	int neighbors = 0;
	for_each_neighbor_pos(p, [this, &neighbors](point p) {
		visual_tile vt = get_tile(p);
		if (vt.state == visual_tile::flagged) {
			++neighbors;
		}
	});
	return neighbors;
}
