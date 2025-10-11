#include "visual_board.h"
#include "mine_board.h"

#include <iostream>

void print_boards(mine_board& mb, visual_board& vb) {
	static bool first = true;
	std::cout << (first ? "" : "\n") << "Mine board:\n";
	for (size_t y = 0; y < mb.height(); ++y) {
		for (size_t x = 0; x < mb.width(); ++x) {
			std::cout << (mb.has_mine({x,y}) ? '*' : '-') << ' ';
		}
		std::cout << '\n';
	}

	std::cout << "\nVisual board:\n";
	for (size_t y = 0; y < mb.height(); ++y) {
		for (size_t x = 0; x < mb.width(); ++x) {
			if (mb.has_mine({x, y})) {
				std::cout << '*';
			} else {
				visual_tile vt = vb.get_tile({x,y});
				std::cout << vt.neighbor_count;
			}
			std::cout << ' ';
		}
		std::cout << '\n';
	}
	first = false;
}

int main() {
	mine_board mb{3,3};
	visual_board vb{mb};

	std::cout << "--Default state--\n";
	print_boards(mb, vb);

	std::cout << "\n--Putting mines onto mine board--\n";
	mb.put_mine({0,0});
	mb.put_mine({1,2});
	mb.put_mine({2,1});
	print_boards(mb, vb);

	std::cout << "\n--Resetting visual board--\n";
	vb.reset();
	print_boards(mb, vb);
}
