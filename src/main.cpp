#include "minesweeper.h"

#include <string>
#include <stdexcept>
#include <cstddef>
#include <iostream>

struct usage_error : std::exception {
	usage_error(const std::string& program) :
		err{"usage: " + program + " <width> <height> <mines>"}
	{}
	const char* what() const noexcept {
		return err.c_str();
	}
	std::string err;
};

int main(int argc, char* argv[]) try {
	if (argc != 4) {
		throw usage_error{argv[0]};
	}
	size_t width;
	size_t height;
	size_t mines;
	try {
		width = std::stoull(argv[1]);
		height = std::stoull(argv[2]);
		mines = std::stoull(argv[3]);
	} catch (...) {
		throw usage_error{argv[0]};
	}
	minesweeper ms{width, height, mines};
	board& b = ms.get();
	b.debug_print();
} catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
