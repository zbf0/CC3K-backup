#include "barrier.h"

BarrierSuit::BarrierSuit(bool g, int x, int y) : Item{'B'}, pos_x{x}, pos_y{y}, isGuarded{g} {}

BarrierSuit::~BarrierSuit() {}

std::string BarrierSuit::report(std::unique_ptr<Player>& p) {
	return "a Barrier Suit";
}

std::vector<std::string> BarrierSuit::itemVisit(ItemVisitor* iv) {
	return iv->visit(this);
}

void BarrierSuit::unguard() {
	isGuarded = false;
}
