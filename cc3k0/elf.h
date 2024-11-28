#include "player.h"

#ifndef ELF_H
#define ELF_H

class Elf : public Player {
	public:
		Elf(int pos_x, int pos_y);
		std::vector<std::string> usePotion(Potion* pot);
		std::string report(std::unique_ptr<Player>& p) override;
		virtual ~Elf();
};

#endif
