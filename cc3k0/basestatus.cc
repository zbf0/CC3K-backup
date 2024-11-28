#include "basestatus.h"

int BaseStatus::getHP(int hp, int max_hp) const {
	return hp;
}

int BaseStatus::getATK(int atk) const {
	return atk;
}

int BaseStatus::getDEF(int def) const {
	return def;
}

std::string BaseStatus::getState() const {
	return "";
}
