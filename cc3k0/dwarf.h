#include "player.h"

#ifndef DWARF_H
#define DWARF_H

class Dwarf : public Player {
	public:
		Dwarf(int pos_x, int pos_y);
		std::vector<std::string> useTreasure(Treasure* tr);
		std::string report(std::unique_ptr<Player>& p) override;
		virtual ~Dwarf();
};

#endif
