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
	bool game_over() const;
private:
	void put_mines(size_t count);

	void control_cursor(char);
	void click(point);
	void toggle_flag(point);
	
	void print_board() const;
	void print_header() const;
	void print_cursor_position() const;
	void print_board_row(size_t row) const;
	void print_tile_separator(point) const;
	void print_tile(point) const;
	void print_footer() const;
	void print_game_over() const;

	enum class state {
		in_progress,
		lose,
		win
	};

	mine_board mb;
	visual_board vb;
	cursor cur;
	state game_state_ = state::in_progress;
};

#endif
