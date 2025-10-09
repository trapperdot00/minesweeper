#include "minesweeper.h"

#include <stdexcept>
#include <string>
#include <cstddef>
#include <iostream>

struct usage_error : std::exception {
	const char* what() const noexcept {
		return "usage: <program> <width> <height> <mines>";
	}
};

struct cli_args {
	cli_args(int argc, char* argv[]) try {
		if (argc < 4) {
			throw usage_error{};
		}
		width = std::stoull(argv[1]);
		height = std::stoull(argv[2]);
		mines = std::stoull(argv[3]);
	} catch (...) {
		throw usage_error{};
	}
	size_t width;
	size_t height;
	size_t mines;
};

int main(int argc, char* argv[]) try {
	cli_args args{argc, argv};
	minesweeper ms{args.width, args.height, args.mines};
	ms.play();
} catch (const std::exception& err) {
	std::cerr << err.what() << '\n';
}
