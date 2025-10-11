#include "board.h"

template <typename tile>
board<tile>::board(size_t width, size_t height, tile init) :
	width_{width},
	height_{height},
	data(height, std::vector<tile>(width, init))
{
	if (width == 0 || height == 0) {
		throw std::invalid_argument{"board size must not be 0"};
	}
}

template <typename tile>
size_t board<tile>::size() const {
	return width_ * height_;
}

template <typename tile>
size_t board<tile>::width() const {
	return width_;
}

template <typename tile>
size_t board<tile>::height() const {
	return height_;
}

template <typename tile>
void board<tile>::reset(tile t) {
	for_each_pos([this, t](point p) {
		data[p.y][p.x] = t;
	});
}

template <typename tile>
bool board<tile>::set_tile(point p, tile t) {
	throw_if_not_in_range(p);
	tile old = data[p.y][p.x];
	if (old == t) {
		return false;
	}
	data[p.y][p.x] = t;
	return true;
}

template <typename tile>
tile board<tile>::get_tile(point p) const {
	throw_if_not_in_range(p);
	return data[p.y][p.x];
}

template <typename tile>
void board<tile>::for_each_pos(std::function<void (point)> f) const {
	for (size_t y = 0; y < height(); ++y) {
		for (size_t x = 0; x < width(); ++x) {
			point p{x, y};
			f(p);
		}
	}
}

template <typename tile>
void board<tile>::for_each_neighbor_pos(point p, std::function<void (point)> f) const {
	for_each_orthogonal_neighbor_pos(p, f);
	for_each_diagonal_neighbor_pos(p, f);
}

template <typename tile>
void board<tile>::for_each_orthogonal_neighbor_pos(point p, std::function<void (point)> f) const {
	if (p.x) {
		f(point{p.x - 1, p.y});
	}
	if (p.y) {
		f(point{p.x, p.y - 1});
	}
	if (p.x + 1 < width()) {
		f(point{p.x + 1, p.y});
	}
	if (p.y + 1 < height()) {
		f(point{p.x, p.y + 1});
	}
}

template <typename tile>
void board<tile>::for_each_diagonal_neighbor_pos(point p, std::function<void (point)> f) const {
	if (p.x && p.y) {
		f(point{p.x - 1, p.y - 1});
	}
	if (p.x + 1 < width() && p.y) {
		f(point{p.x + 1, p.y - 1});
	}
	if (p.x && p.y + 1 < height()) {
		f(point{p.x - 1, p.y + 1});
	}
	if (p.x + 1 < width() && p.y + 1 < height()) {
		f(point{p.x + 1, p.y + 1});
	}
}

template <typename tile>
bool board<tile>::is_in_range(point p) const {
	return p.x < width_ && p.y < height_;
}

template <typename tile>
void board<tile>::throw_if_not_in_range(point p) const {
	if (!is_in_range(p)) {
		throw std::out_of_range{"Point out-of-range"};
	}
}
