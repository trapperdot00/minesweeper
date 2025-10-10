#ifndef VISUAL_TILE_H
#define VISUAL_TILE_H

struct visual_tile {
	enum {
		clickable,
		clicked,
		flagged
	} state = clickable;
	int neighbor_count = 0;
};

bool operator==(const visual_tile&, const visual_tile&);
bool operator!=(const visual_tile&, const visual_tile&);

#endif
