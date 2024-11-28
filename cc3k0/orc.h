#include "player.h"

#ifndef ORC_H
#define ORC_H

class Orc : public Player {
	public:
		Orc(int pos_x, int pos_y);
		std::vector<std::string> useTreasure(Treasure* tr);
		std::string report(std::unique_ptr<Player>& p) override;
		virtual ~Orc();
};

#endif
