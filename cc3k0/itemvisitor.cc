#include "itemvisitor.h"

ItemVisitor::ItemVisitor(Player* p) : p{p} {}

std::vector<std::string> ItemVisitor::visit(Potion* pot) {
	return p->usePotion(pot);
}

std::vector<std::string> ItemVisitor::visit(Treasure* tr) {
	return p->useTreasure(tr);
}

std::vector<std::string> ItemVisitor::visit(Compass* c) {
	return p->useCompass(c);
}

std::vector<std::string> ItemVisitor::visit(BarrierSuit* b) {
	return p->useBarrierSuit(b);
}
