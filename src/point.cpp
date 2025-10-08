#include "point.h"

#include <iostream>

std::istream& operator>>(std::istream& is, point& p) {
	return is >> p.x >> p.y;
}

std::ostream& operator<<(std::ostream& os, const point& p) {
	return os << '(' << p.x << ';' << p.y << ')';
}
