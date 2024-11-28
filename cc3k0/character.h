#include "entity.h"
#include <math.h>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public Entity {
	public:
		int hp;
		int max_hp;
		int atk;
		int def;
		int gold;
		Character(int hp, int max_hp, int atk, int def, int gold, int pos_x, int pos_y, char map_symbol);
		void die();
		void set_compass(bool compass);
		virtual ~Character() = 0;
};

#endif
