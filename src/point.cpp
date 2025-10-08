#include "point.h"

#include <iostream>

bool operator==(const point& lhs, const point& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const point& lhs, const point& rhs) {
	return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, point& p) {
	return is >> p.x >> p.y;
}

std::ostream& operator<<(std::ostream& os, const point& p) {
	return os << '(' << p.x << ';' << p.y << ')';
}
