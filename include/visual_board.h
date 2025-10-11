#ifndef VISUAL_BOARD_H
#define VISUAL_BOARD_H

#include "board.h"
#include "visual_tile.h"
#include "mine_board.h"
#include "point.h"

#include <cstddef>

class visual_board : public board<visual_tile> {
public:
	explicit visual_board(const mine_board& mb);

	void reset();
	void update_neighbor_counts();

	bool click(point);
	bool toggle_flag(point);

	size_t clickable_count() const;
	size_t clicked_count() const;
	size_t flagged_count() const;

	void clear_tile(point, point* parent = nullptr);
	int flagged_neighbors_count(point) const;

private:
	size_t clicked_count_ = 0;
	size_t flagged_count_ = 0;
	const mine_board& mb_;
};

#endif
