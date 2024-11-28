#include "attackvisitor.h"

AttackVisitor::AttackVisitor(Player* p) : p{p} {}

std::vector<std::string> AttackVisitor::visit(Enemy* e) {
	return p->attack(e);
}

