#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"
#include "player.h"
#include "treasure.h"

#include <iostream>

class Dragon : public Enemy {
	public:
		Dragon(int pos_x, int pos_y, int treasure_x = 0, int treasure_y = 0);
		std::string report(std::unique_ptr<Player>& p) override;
		~Dragon();
	private:
		bool hostile(std::unique_ptr<Player>& p) override;
		std::string die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) override;
		std::vector<int>* get_slot(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) override;
};

#endif
