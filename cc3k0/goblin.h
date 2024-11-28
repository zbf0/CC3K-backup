#ifndef GOBLIN_H
#define GOBLIN_H

#include "enemy.h"
#include "player.h"

class Goblin : public Enemy {
	public:
		Goblin(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		~Goblin();
	private:
		std::string attack_ability(std::unique_ptr<Player>& p) override;
};

#endif
