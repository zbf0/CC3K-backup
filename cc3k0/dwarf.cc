#include "dwarf.h"
#include "treasure.h"

Dwarf::Dwarf(int pos_x, int pos_y) : Player(100, 20, 30, pos_x, pos_y) {}

std::vector<std::string> Dwarf::useTreasure(Treasure* tr) {
	return gainGold(tr->size * 2);
}

std::string Dwarf::report(std::unique_ptr<Player>& p) {
       return "a Dwarf";
}       

Dwarf::~Dwarf() {}
