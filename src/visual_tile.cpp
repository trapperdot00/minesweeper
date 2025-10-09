#include "visual_tile.h"

bool operator==(const visual_tile& lhs, const visual_tile& rhs) {
	return lhs.state == rhs.state && lhs.neighbor_count == rhs.neighbor_count;
}

bool operator!=(const visual_tile& lhs, const visual_tile& rhs) {
	return !(lhs == rhs);
}
