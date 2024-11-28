#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "enemy.h"
#include "player.h"

class Vampire : public Enemy {
	public:
		Vampire(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		~Vampire();
	private:
		std::string attack_ability(std::unique_ptr<Player>& p) override;
};

#endif
