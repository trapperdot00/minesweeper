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
private:
	void put_mines(size_t count);
	
	void print_board() const;
	void print_header() const;
	void print_cursor_position() const;
	void print_board_row(size_t row) const;
	void print_tile_separator(point) const;
	void print_tile(point) const;
	void print_footer() const;

	void control_cursor(char);

	mine_board mb;
	visual_board vb;
	cursor cur;
};

#endif
