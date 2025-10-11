#include "minesweeper.h"

#include "point.h"

#include <stdexcept>
#include <random>
#include <chrono>
#include <cctype>
#include <iostream>
#include <iomanip>

minesweeper::minesweeper(size_t width, size_t height, size_t mine_count) :
	mine_count_{mine_count},
	mb{width, height},
	vb{mb},
	cur{point{0, 0}, width, height,
		[this](point p) { click(p); },
		[this](point p) { toggle_flag(p); }
	}
{
	if (mine_count == 0) {
		throw std::invalid_argument{"game requires at least one mine"};
	} else if (width * height <= mine_count) {
		throw std::invalid_argument{"no space for mines, game requires at least one empty field"};
	}
}

void minesweeper::play() {
	if (!board_empty) {
		reset();
	}
	print_board();
	for (char ch; !game_over() && std::cin.get(ch); ) {
		if (ch == '\n') {
			continue;
		}
		control_cursor(ch);
		if (game_over() || std::cin.peek() == '\n') {
			print_board();
		}
	}
	print_game_over();
}

void minesweeper::reset() {
	mb.reset();
	vb.reset();
	cur.move(point{0, 0});
	game_state_ = state::in_progress;
	board_empty = true;
}

bool minesweeper::game_over() const {
	return game_state_ != state::in_progress;
}

size_t minesweeper::board_area() const {
	return board_width() * board_height();
}

size_t minesweeper::board_width() const {
	return mb.width();
}

size_t minesweeper::board_height() const {
	return mb.height();
}

size_t minesweeper::mine_count() const {
	return mine_count_;
}

minesweeper::state minesweeper::game_state() const {
	return game_state_;
}

void minesweeper::put_mines(point except_to) {
	static std::default_random_engine rengine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<size_t> x_gen(0, board_width() - 1);
	static std::uniform_int_distribution<size_t> y_gen(0, board_height() - 1);
	for (size_t count = mine_count_; count; ) {
		point candidate{x_gen(rengine), y_gen(rengine)};
		if (candidate != except_to && !mb.has_mine(candidate)) {
			mb.put_mine(candidate);
			--count;
		}
	}
	vb.update_neighbor_counts();
	board_empty = false;
}

void minesweeper::control_cursor(char ch) {
	switch (std::tolower(ch)) {
	case 'w':
		cur.move(cursor::up);
		break;
	case 's':
		cur.move(cursor::down);
		break;
	case 'd':
		cur.move(cursor::right);
		break;
	case 'a':
		cur.move(cursor::left);
		break;
	case ' ': case 'x':
		cur.click();
		break;
	case 'f':
		cur.alt_click();
		break;
	}
}

void minesweeper::click(point p) {
	if (board_empty) {
		put_mines(p);
	}
	visual_tile old_vt = vb.get_tile(p);
	vb.click(p);
	update_game_state(p, old_vt);
	if (vb.get_tile(p).state == visual_tile::clicked) {
		try_clear_unflagged_neighbors(p);
	}
}

void minesweeper::toggle_flag(point p) {
	vb.toggle_flag(p);
}

void minesweeper::update_game_state(point p, visual_tile old) {
	if (old.state == visual_tile::clickable && mb.has_mine(p)) {
		game_state_ = state::lose;
	} else if (vb.clicked_count() == mb.empty_count()) {
		game_state_ = state::win;
	}
}

void minesweeper::try_clear_unflagged_neighbors(point p) {
	visual_tile vt = vb.get_tile(p);
	if (vt.neighbor_count == 0 || vt.neighbor_count != vb.flagged_neighbors_count(p)) {
		return;
	}
	mb.for_each_neighbor_pos(p, [this](point neighbor){
		visual_tile neighbor_vt = vb.get_tile(neighbor);
		if (neighbor_vt.state != visual_tile::clickable) {
			return;
		}
		vb.clear_tile(neighbor);
		if (mb.has_mine(neighbor)) {
			game_state_ = state::lose;
		} else if (vb.clicked_count() == mb.empty_count()) {
			game_state_ = state::win;
		}
	});
}

void minesweeper::print_board() const {
	print_header();
	for (size_t row = 0; row < mb.height(); ++row) {
		print_board_row(row);
	}
	print_footer();
}

void minesweeper::print_header() const {
	size_t footer_width = 2 * mb.width() + 3;
	std::cout << std::setfill('-') << std::setw(footer_width) << '\n';
}

void minesweeper::print_cursor_position() const {
	std::cout << "pos: " << cur.pos() << '\n';
}

void minesweeper::print_board_row(size_t row) const {
	std::cout << '|';
	for (size_t column = 0; column < mb.width(); ++column) {
		point p{column, row};
		print_tile_separator(p);
		print_tile(p);
	}
	std::cout << '|';
	std::cout << '\n';
}

void minesweeper::print_tile_separator(point p) const {
	if (!game_over() && cur.pos() == p) {
		std::cout << '>';
	} else {
		std::cout << ' ';
	}
}

void minesweeper::print_tile(point p) const {
	visual_tile vt = vb.get_tile(p);
	switch (vt.state) {
	case visual_tile::clicked:
		if (mb.has_mine(p)) {
			std::cout << '*';
		} else if (vt.neighbor_count) {
			std::cout << vt.neighbor_count;
		} else {
			std::cout << ' ';
		}
		break;
	case visual_tile::flagged:
		if (game_state() == state::lose && mb.has_mine(p)) {
			std::cout << '*';
		} else {
			std::cout << 'P';
		}
		break;
	case visual_tile::clickable:
		if (game_over() && mb.has_mine(p)) {
			std::cout << (game_state() == state::win ? 'P' : '*');
		}  else {
			std::cout << '.';
		}
		break;
	default:
		break;
	}
}

void minesweeper::print_footer() const {
	print_header();
}

void minesweeper::print_game_over() const {
	switch (game_state_) {
	case state::lose:
		std::cout << "\nYou lost!\n";
		break;
	case state::win:
		std::cout << "\nHooray, you won!\n";
		break;
	default:
		break;
	}
}
