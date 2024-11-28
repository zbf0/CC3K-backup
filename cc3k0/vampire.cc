#include "vampire.h"
#include <string>

Vampire::Vampire(int pos_x, int pos_y) : Enemy{50, 25, 25, pos_x, pos_y, 'V'} {}

std::string Vampire::report(std::unique_ptr<Player>& p) {
        std::string r = "a Vampire(";
        r += std::to_string(hp) += ")";
        return r;
}

Vampire::~Vampire() {}

std::string Vampire::attack_ability(std::unique_ptr<Player>& p) {
	int steal_hp = atk * 100 / (100 + p->def) / 2;
	if (p->barrier) {
		steal_hp /= 2;
	}
	if (steal_hp > p->hp) steal_hp = p->hp;
	hp += steal_hp;
	if (hp > 50) {
		hp = 50;
	}
	std::string abilityReport = "";
	abilityReport += map_symbol;
	abilityReport += " (" + std::to_string(hp) + " HP) stole " + std::to_string(steal_hp) + " of your life points!";
	return abilityReport;
}
