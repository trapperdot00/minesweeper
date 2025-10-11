#include "point.h"
#include "mine_board.h"
#include "visual_board.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cctype>

void print_visual_board(visual_board& vb) {
	std::cout << "\nVisual board:\n";
	std::cout << "Clickable: " << vb.clickable_count() << '\n'
			  << "Clicked: " << vb.clicked_count() << '\n'
			  << "Flagged: " << vb.flagged_count() << '\n';
	for (size_t y = 0; y < vb.height(); ++y) {
		for (size_t x = 0; x < vb.width(); ++x) {
			visual_tile vt = vb.get_tile({x, y});
			switch (vt.state) {
			case visual_tile::clickable:
				std::cout << '#';
				break;
			case visual_tile::clicked:
				if (vt.neighbor_count) {
					std::cout << vt.neighbor_count;
				} else {
					std::cout << ' ';
				}
				break;
			case visual_tile::flagged:
				std::cout << 'P';
				break;
			default:
				break;
			}
			std::cout << ' ';
		}
		std::cout << '\n';
	}
}

void print_mine_board(mine_board& mb) {
	std::cout << "Mine board:\n";
	std::cout << "Mines: " << mb.mine_count() << '\n'
			  << "Empty: " << mb.empty_count() << '\n';
	for (size_t y = 0; y < mb.height(); ++y) {
		for (size_t x = 0; x < mb.width(); ++x) {
			std::cout << (mb.has_mine({x, y}) ? '*' : '-') << ' ';
		}
		std::cout << '\n';
	}
}

void print_available_commands() {
	std::cout << "Available commands:\n"
			  << "\tVisual:\n"
			  << "\t\tc <x> <y>: click a tile\n"
			  << "\t\tf <x> <y>: toggle flag on a tile\n"
			  << "\t\trv: reset\n"
			  << "\t\tu: update neighbor counts\n"
			  << "\tMine:\n"
			  << "\t\tp <x> <y>: place mine\n"
			  << "\t\te <x> <y>: erase mine\n"
			  << "\t\trm: reset\n";
}

point get_point(std::istream& is) {
	point p;
	if (!(is >> p)) {
		throw std::invalid_argument{"invalid point"};
	}
	return p;
}

int main() {
	mine_board mb{4, 4};
	visual_board vb{mb};

	print_mine_board(mb);
	print_visual_board(vb);
	std::cout << "\n> ";
	for (char action = 0; std::cin >> action; ) {
		switch (std::tolower(action)) {
		case 'c':
			vb.click(get_point(std::cin));
			break;
		case 'f':
			vb.toggle_flag(get_point(std::cin));
			break;
		case 'p':
			mb.put_mine(get_point(std::cin));
			break;
		case 'e':
			mb.erase_mine(get_point(std::cin));
			break;
		case 'r':
			if (!(std::cin.get(action))) {
				break;
			}
			if (action == 'm') {
				mb.reset();
			}
			if (action == 'v') {
				vb.reset();
			}
			break;
		case 'u':
			vb.update_neighbor_counts();
			break;
		default:
			print_available_commands();
			std::cout << "> ";
			continue;
		}
		if (std::cin) {
			print_mine_board(mb);
			print_visual_board(vb);
			std::cout << "\n> ";
		}
	}
}
