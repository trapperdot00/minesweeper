#include "minesweeper.h"

#include "point.h"

#include <stdexcept>
#include <random>
#include <chrono>
#include <cctype>
#include <iostream>
#include <iomanip>

minesweeper::minesweeper(size_t width, size_t height, size_t mine_count) :
	mb{width, height},
	vb{mb},
	cur{point{width / 2, height / 2}, width, height,
		[this](point p) { click(p); },
		[this](point p) { toggle_flag(p); }
	}
{
	if (mine_count == 0) {
		game_state_ = state::win;
	} else if (width * height <= mine_count) {
		throw std::invalid_argument{"no space for mines, game requires at least one empty field"};
	} else {
		put_mines(mine_count);
	}
}

void minesweeper::play() {
	print_board();
	for (char ch; !game_over() && std::cin >> ch; ) {
		control_cursor(ch);
		print_board();
	}
	print_game_over();
}

bool minesweeper::game_over() const {
	return game_state_ != state::in_progress;
}

void minesweeper::put_mines(size_t count) {
	static std::default_random_engine rengine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<size_t> x_gen(0, mb.width() - 1);
	static std::uniform_int_distribution<size_t> y_gen(0, mb.height() - 1);
	while (count) {
		point candidate{x_gen(rengine), y_gen(rengine)};
		if (!mb.has_mine(candidate)) {
			mb.put_mine(candidate);
			--count;
		}
	}
	vb.update_neighbor_counts();
}

void minesweeper::control_cursor(char ch) {
	switch (std::tolower(ch)) {
	case 'u':
		cur.move(cursor::up);
		break;
	case 'd':
		cur.move(cursor::down);
		break;
	case 'r':
		cur.move(cursor::right);
		break;
	case 'l':
		cur.move(cursor::left);
		break;
	case 'x':
		cur.click();
		break;
	case 'f':
		cur.alt_click();
		break;
	}
}

void minesweeper::click(point p) {
	if (!vb.click(p)) {
		return;
	}
	if (mb.has_mine(p)) {
		game_state_ = state::lose;
	} else if (vb.clicked_count() == mb.empty_count()) {
		game_state_ = state::win;
	}
}

void minesweeper::toggle_flag(point p) {
	vb.toggle_flag(p);
}

void minesweeper::print_board() const {
	//print_cursor_position();
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
	std::cout << (cur.pos() == p ? '>' : ' ');
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
		std::cout << 'P';
		break;
	case visual_tile::clickable:
		std::cout << '#';
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
