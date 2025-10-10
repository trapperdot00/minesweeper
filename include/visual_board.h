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

	void update_neighbor_counts();

	bool click(point);
	bool toggle_flag(point);

	size_t clicked_count() const;
private:
	const mine_board& mb_;
};

#endif
