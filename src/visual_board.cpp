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
	return size() - clicked_count() - flagged_count();
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
	// Launch orthogonal clearers
	if (p.x) {
		clear_tile(point{p.x - 1, p.y}, &p);
	}
	if (p.y) {
		clear_tile(point{p.x, p.y - 1}, &p);
	}
	if (p.x + 1 < width()) {
		clear_tile(point{p.x + 1, p.y}, &p);
	}
	if (p.y + 1 < height()) {
		clear_tile(point{p.x, p.y + 1}, &p);
	}
	// Launch diagonal clearers
	if (p.x && p.y) {
		clear_tile(point{p.x - 1, p.y - 1}, &p);
	}
	if (p.x + 1 < width() && p.y) {
		clear_tile(point{p.x + 1, p.y - 1}, &p);
	}
	if (p.x && p.y + 1 < height()) {
		clear_tile(point{p.x - 1, p.y + 1}, &p);
	}
	if (p.x + 1 < width() && p.y + 1 < height()) {
		clear_tile(point{p.x + 1, p.y + 1}, &p);
	}
}

int visual_board::flagged_neighbors_count(point p) const {
	int neighbors = 0;
	const size_t min_y = std::min(p.y - 1, p.y);
	const size_t max_y = std::min(height() - 1, p.y + 1);
	for (size_t y = min_y; y <= max_y; ++y) {
		const size_t min_x = std::min(p.x - 1, p.x);
		const size_t max_x = std::min(width() - 1, p.x + 1);
		for (size_t x = min_x; x <= max_x; ++x) {
			point p{x, y};
			if (get_tile(p).state == visual_tile::flagged) {
				++neighbors;
			}
		}
	}
	return neighbors;
}
