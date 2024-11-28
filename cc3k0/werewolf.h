#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "enemy.h"

class Werewolf : public Enemy {
	public:
		Werewolf(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		~Werewolf();

};

#endif
