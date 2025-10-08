#ifndef POINT_H
#define POINT_H

#include <cstddef>
#include <iosfwd>

struct point {
	size_t x;
	size_t y;
};

std::istream& operator>>(std::istream&, point&);
std::ostream& operator<<(std::ostream&, const point&);

#endif
