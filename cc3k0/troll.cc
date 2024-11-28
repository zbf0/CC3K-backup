#include "troll.h"
#include <string>

Troll::Troll(int pos_x, int pos_y) : Enemy{120, 25, 15, pos_x, pos_y, 'T'} {}

std::string Troll::report(std::unique_ptr<Player>& p) {
        std::string r = "a Troll(";
        r += std::to_string(hp) += ")";
        return r;
}

Troll::~Troll() {}

std::string Troll::passive_ability() {
	std::string abilityReport = "";
	int heal_factor = 3;

	hp += heal_factor;
	if (hp > 120) {
		hp = 120;
	} else {
		abilityReport += map_symbol;
		abilityReport += " (" + std::to_string(hp) + " HP) healed " + std::to_string(heal_factor) + " HP.";
	}

	return abilityReport;
}
