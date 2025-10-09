#include "cursor.h"

cursor::cursor(point start, size_t width, size_t height,
		std::function<void (point)> callback) :
	pos_{start},
	width_{width},
	height_{height},
	click_event{callback}
{}

void cursor::move(direction d) {
	switch (d) {
	case up:
		pos_.y -= (pos_.y) ? 1 : 0;
		break;
	case down:
		pos_.y += (pos_.y + 1 < height_) ? 1 : 0;
		break;
	case right:
		pos_.x += (pos_.x + 1 < width_) ? 1 : 0;
		break;
	case left:
		pos_.x -= (pos_.x) ? 1 : 0;
		break;
	}
}

void cursor::click() {
	click_event(pos_);
}

point cursor::pos() const {
	return pos_;
}

size_t cursor::width() const {
	return width_;
}

size_t cursor::height() const {
	return height_;
}
