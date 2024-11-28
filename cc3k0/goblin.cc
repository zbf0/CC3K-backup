#include "goblin.h"
#include <string>

Goblin::Goblin(int pos_x, int pos_y) : Enemy{70, 5, 10, pos_x, pos_y, 'N'} {}

std::string Goblin::report(std::unique_ptr<Player>& p) {
        std::string r = "a Goblin(";
        r += std::to_string(hp) += ")";
        return r;
}

Goblin::~Goblin() {}

std::string Goblin::attack_ability(std::unique_ptr<Player>& p) {
	std::string abilityReport = "";
	abilityReport += map_symbol;
	abilityReport += " (" + std::to_string(hp);

	int gold_stolen = 1;
	p->gold -= gold_stolen;

	if (p->gold < 0) {
		p->gold = 0;
		return abilityReport += " HP) tried to pickpocket... but you're too broke.";
	} else {
		return abilityReport += " HP) pickpocketed " + std::to_string(gold_stolen) + " gold while you weren't looking!";
	}
}
