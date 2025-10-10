#include "mine_board.h"

#include <iostream>

int main() {
	mine_board mb{3, 3};
	mb.put_mine({1,1});
	mb.put_mine({0,0});
	mb.put_mine({2,0});
	mb.put_mine({0,2});
	mb.put_mine({2,2});
	std::cout << "Mines (" << mb.mine_count() << "):\n";
	for (size_t y = 0; y < 3; ++y) {
		for (size_t x = 0; x < 3; ++x) {
			std::cout << (mb.has_mine({x,y}) ? '*' : '-') << ' ';
		}
		std::cout << '\n';
	}
	mb.reset();
	std::cout << "\nAfter reset (" << mb.mine_count() << "):\n";
	for (size_t y = 0; y < 3; ++y) {
		for (size_t x = 0; x < 3; ++x) {
			std::cout << (mb.has_mine({x,y}) ? '*' : '-') << ' ';
		}
		std::cout << '\n';
	}
}
