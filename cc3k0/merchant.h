#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"
#include "player.h"
#include "treasure.h"

class Merchant : public Enemy {
	public:
		Merchant(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		~Merchant();
	private:
		bool hostile(std::unique_ptr<Player>& p) override;
		std::string die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) override;
};

#endif
