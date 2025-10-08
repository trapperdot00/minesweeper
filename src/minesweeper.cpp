#include "minesweeper.h"

#include <stdexcept>
#include <random>
#include <chrono>

minesweeper::minesweeper(size_t width, size_t height, size_t mine_count) :
	b{width, height}
{
	if (width * height <= mine_count) {
		throw std::invalid_argument{"no space for mines, game requires at least one empty field"};
	}
	put_mines(mine_count);
}

void minesweeper::put_mines(size_t count) {
	static std::default_random_engine rengine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<size_t> x_gen(0, b.width() - 1);
	static std::uniform_int_distribution<size_t> y_gen(0, b.height() - 1);
	while (count) {
		point candidate{x_gen(rengine), y_gen(rengine)};
		if (!b.has_mine(candidate)) {
			b.put_mine(candidate);
			--count;
		}
	}
}
