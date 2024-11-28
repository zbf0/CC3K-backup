#include "item.h"

Item::Item(char map_symbol) : Entity{0, 0, map_symbol} {}

void Item::print_map_symbol() {
	std::cout << "\033[36m" << map_symbol << "\033[0m";
}

Item::~Item() {}
