#include "minesweeper.h"

#include <iostream>
#include <cstddef>
#include <limits>

int main() {
	size_t rounds = 0;
	size_t wins = 0;
	size_t loses = 0;
	minesweeper ms{10, 10, 10};

	std::cout << "Enter rounds: ";
	if (std::cin >> rounds) {
		for (size_t i = 0; i < rounds; ++i) {
			std::cout << "\nRound #" << i << ":\n";
			ms.play();
			switch (ms.game_state()) {
			case minesweeper::state::win:
				++wins;
				break;
			case minesweeper::state::lose:
				++loses;
				break;
			default:
				break;
			}
			ms.reset();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cout << "----------------------------\n"
				  << "Wins:\t" << wins << '\n'
				  << "Loses:\t" << loses << '\n';
	}
}
