#ifndef CURSOR_H
#define CURSOR_H

#include "point.h"

#include <cstddef>
#include <functional>

class cursor {
public:
	cursor(point start, size_t width, size_t height,
			std::function<void (point)> cb,
			std::function<void (point)> alt_cb);

	enum direction {
		up,
		down,
		right,
		left
	};

	void move(direction);
	void move(point);

	void click();
	void alt_click();

	point pos() const;
	size_t width() const;
	size_t height() const;
private:
	point pos_;
	size_t width_;
	size_t height_;
	std::function<void (point)> click_event;
	std::function<void (point)> alt_click_event;
};

#endif
