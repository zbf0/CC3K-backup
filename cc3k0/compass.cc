#include "compass.h"

Compass::Compass(int x, int y) : Item{'C'}, pos_x{x}, pos_y{y} {}

Compass::~Compass() {}

std::string Compass::report(std::unique_ptr<Player>& p) {
	return "a Compass";
}

std::vector<std::string> Compass::itemVisit(ItemVisitor* iv) {
	return iv->visit(this);
}

void Compass::print_map_symbol() {
	std::cout << "\033[1;33m" << map_symbol << "\033[0m";
}
