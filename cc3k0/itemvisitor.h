#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

#include "player.h"
class Potion;
class Treasure;

class ItemVisitor {
	Player* p;
	public:
		ItemVisitor(Player* p);
		std::vector<std::string> visit(Potion* pot);
		std::vector<std::string> visit(Treasure* tr);
		std::vector<std::string> visit(Compass* c);
		std::vector<std::string> visit(BarrierSuit* b);
};

#endif
