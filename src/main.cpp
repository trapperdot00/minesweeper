#include "board.h"

#include <string>
#include <stdexcept>
#include <cstddef>
#include <iostream>

struct usage_error : std::exception {
	usage_error(const std::string& program) :
		err{"usage: " + program + " <width> <height>"}
	{}
	const char* what() const noexcept {
		return err.c_str();
	}
	std::string err;
};

int main(int argc, char* argv[]) try {
	if (argc != 3) {
		throw usage_error{argv[0]};
	}
	size_t width;
	size_t height;
	try {
		width = std::stoull(argv[1]);
		height = std::stoull(argv[2]);
	} catch (...) {
		throw usage_error{argv[0]};
	}
	board b{width, height};

	char action;
	point p;
	while (std::cin >> action >> p) {
		switch (action) {
		case 'p':
			b.put_mine(p);
			break;
		case 'e':
			b.erase_mine(p);
			break;
		}
		b.debug_print();
	}
} catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
