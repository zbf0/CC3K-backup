#ifndef TROLL_H
#define TROLL_H

#include "enemy.h"
#include "player.h"

class Troll : public Enemy {
	public:
		Troll(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		~Troll();
	private:
		std::string passive_ability() override;
};

#endif
