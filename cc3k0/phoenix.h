#ifndef PHOENIX_H
#define PHOENIX_H

#include "enemy.h"
#include "player.h"

class Phoenix : public Enemy {
	public:
		Phoenix(int pos_x, int pos_y, bool revived = false);
		std::string report(std::unique_ptr<Player>& p) override;
		~Phoenix();
	private:
		std::string die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) override;
};

#endif
