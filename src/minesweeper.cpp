#include "minesweeper.h"

#include "point.h"

#include <stdexcept>
#include <random>
#include <chrono>
#include <cctype>

minesweeper::minesweeper(size_t width, size_t height, size_t mine_count) :
	mb{width, height},
	vb{mb},
	pos{point{width / 2, height / 2}, width, height, [this](point p) {
		halo(p);
	}}
{
	if (width * height <= mine_count) {
		throw std::invalid_argument{"no space for mines, game requires at least one empty field"};
	}
	put_mines(mine_count);
}

void minesweeper::play() {
	mb.debug_print();
	vb.debug_print();
	for (char ch; std::cin >> ch; ) {
		cursor::direction dir;
		switch (std::tolower(ch)) {
		case 'u':
			pos.move(cursor::up);
			break;
		case 'd':
			pos.move(cursor::down);
			break;
		case 'r':
			pos.move(cursor::right);
			break;
		case 'l':
			pos.move(cursor::left);
			break;
		case 'x':
			pos.click();
			break;
		}
		mb.debug_print();
		vb.debug_print();
	}
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
