#include "minesweeper.h"

#include "point.h"

#include <stdexcept>
#include <random>
#include <chrono>
#include <cctype>
#include <iostream>

minesweeper::minesweeper(size_t width, size_t height, size_t mine_count) :
	mb{width, height},
	vb{mb},
	cur{point{width / 2, height / 2}, width, height, [this](point p) {
		click(p);
	}}
{
	if (width * height <= mine_count) {
		throw std::invalid_argument{"no space for mines, game requires at least one empty field"};
	}
	put_mines(mine_count);
}

void minesweeper::play() {
	std::cout << "pos: " << cur.pos() << '\n';
	print();
	std::cout << "----------------------\n\n";
	for (char ch; std::cin >> ch; ) {
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
		}
		std::cout << "\npos: " << cur.pos() << '\n';
		print();
		std::cout << "----------------------\n\n";
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

void minesweeper::click(point p) {
	vb.click(p);
}

void minesweeper::print() const {
	for (size_t y = 0; y < mb.height(); ++y) {
		for (size_t x = 0; x < mb.width(); ++x) {
			point p{x, y};
			visual_tile vt = vb.get_tile(p);
			std::cout << (cur.pos() == p ? '>' : ' ');
			if (vt.state == visual_tile::clicked) {
				if (mb.has_mine(p)) {
					std::cout << '*';
				} else {
					std::cout << vt.neighbor_count;
				}
			} else {
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
}
