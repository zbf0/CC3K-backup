#include "merchant.h"
#include <string>

Merchant::Merchant(int pos_x, int pos_y) : Enemy{30, 70, 5, pos_x, pos_y, 'M'} {
	gold = 0;
}

std::string Merchant::report(std::unique_ptr<Player>& p) {
        std::string r = "a Merchant(";
        r += std::to_string(hp) += ")";
        return r;
}

Merchant::~Merchant() {}

bool Merchant::hostile(std::unique_ptr<Player>& p) {
	return p->merchant_hostile;
}

std::string Merchant::die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) {
	entitymap->at(pos_x)[pos_y] = std::move(std::make_unique<Treasure>(4));
	std::string deathReport = "";
	deathReport += map_symbol;
	return deathReport += " (" + std::to_string(hp) + " HP) dropped a Merchant Hoard!";
}
