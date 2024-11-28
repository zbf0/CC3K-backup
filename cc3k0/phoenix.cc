#include "phoenix.h"
#include <string>

Phoenix::Phoenix(int pos_x, int pos_y, bool revived) : Enemy{50, 35, 25, pos_x, pos_y, 'X'} {
	if (revived) {
		hp = 25;
		def = 0;
	}
}

std::string Phoenix::report(std::unique_ptr<Player>& p) {
        std::string r = "a Phoenix(";
        r += std::to_string(hp) += ")";
        return r;
}

Phoenix::~Phoenix() {}

std::string Phoenix::die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) {
	std::string deathReport = "";
	if (def) {
		entitymap->at(pos_x)[pos_y] = std::move(std::make_unique<Phoenix>(pos_x, pos_y, true));
		deathReport += ".. but another ";
		deathReport += map_symbol;
		deathReport += " (25 HP) rises from its ashes!";
	}

	return deathReport;
}
