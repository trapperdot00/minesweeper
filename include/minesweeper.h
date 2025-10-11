#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mine_board.h"
#include "visual_board.h"
#include "cursor.h"

#include <cstddef>
#include <iostream>

class minesweeper {
public:
	minesweeper(size_t width, size_t height, size_t mine_count);

	void play();
	void reset();

	bool game_over() const;
	size_t board_area() const;
	size_t board_width() const;
	size_t board_height() const;
	size_t mine_count() const;

	enum class state {
		in_progress,
		lose,
		win
	};
	state game_state() const;
private:
	void put_mines(point except_to);

	void control_cursor(char);
	void click(point);
	void toggle_flag(point);

	void try_clear_unflagged_neighbors(point);
	
	void print_board() const;
	void print_header() const;
	void print_cursor_position() const;
	void print_board_row(size_t row) const;
	void print_tile_separator(point) const;
	void print_tile(point) const;
	void print_footer() const;
	void print_game_over() const;

	size_t mine_count_ = 0;
	mine_board mb;
	visual_board vb;
	cursor cur;
	state game_state_ = state::in_progress;
	bool board_empty = true;
};

#endif
