#ifndef ATTACKVISITOR_H
#define ATTACKVISITOR_H

#include "player.h"
class Enemy;

class AttackVisitor {
	Player* p;
	public:
		AttackVisitor(Player* p);
		std::vector<std::string> visit(Enemy* e);
};

#endif
