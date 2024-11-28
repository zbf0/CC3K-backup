#include "orc.h"
#include "treasure.h"

Orc::Orc(int pos_x, int pos_y) : Player(180, 30, 25, pos_x, pos_y) {}

std::vector<std::string> Orc::useTreasure(Treasure* tr) {
	return gainGold(tr->size / 2);
}

std::string Orc::report(std::unique_ptr<Player>& p) {
	return "an Orc";
}

Orc::~Orc() {}
