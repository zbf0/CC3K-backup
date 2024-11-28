#include "treasure.h"

Treasure::Treasure(int size, bool g, int x, int y) : Item{'G'}, pos_x{x}, pos_y{y}, size{size}, isGuarded{g} {}

Treasure::~Treasure() {}

std::string Treasure::report(std::unique_ptr<Player>& p) {
	switch (size){
		case 1:
			return "a Normal Gold Pile";
		break;
		case 2:
			return "a Small Hoard";
		break;
		case 4:
			return "a Merchant Hoard";
		break;
		case 6:
			return "a Dragon Hoard";
		break;
		default:
			return "a Gold Pile";
		break;
	}
}

std::vector<std::string> Treasure::itemVisit(ItemVisitor* iv) {
	return iv->visit(this);
}

void Treasure::print_map_symbol() {
	std::cout << "\033[1;33m" << map_symbol << "\033[0m";
}

void Treasure::unguard() {
	isGuarded = false;
}
