#include "tempPotion.h"
#include <iostream>

TempPotion::TempPotion(std::shared_ptr<PlayerStatus> ps, int type, int effect) : PotionDecorator{ps}, type{type}, effect{effect} {}

int TempPotion::getHP(int hp, int max_hp) const {
	if (effect == 0) {
		if (playerStatus->getHP(hp, max_hp) + 10 > max_hp) return max_hp;
		return playerStatus->getHP(hp, max_hp) + 10;
	} else if (effect == 3) {
		if (playerStatus->getHP(hp, max_hp) < 10) return 0;
		return playerStatus->getHP(hp, max_hp) - 10;
	}
	return playerStatus->getHP(hp, max_hp);
}

int TempPotion::getATK(int atk) const {
	if (effect == 1) {
		return playerStatus->getATK(atk) + 5;
	} else if (effect == 4) {
		if (playerStatus->getATK(atk) < 5) return 0;
		return playerStatus->getATK(atk) - 5;
	}
	return playerStatus->getATK(atk);
}

int TempPotion::getDEF(int def) const {
	if (effect == 2) {
		return playerStatus->getDEF(def) + 5;
	} else if (effect == 5) {
		if (playerStatus->getDEF(def) < 5) return 0;
		return playerStatus->getDEF(def) - 5;
	}
	return playerStatus->getDEF(def);
}

std::string TempPotion::getState() const {
	std::string s = std::to_string(type);
	return s + playerStatus->getState();
}

TempPotion::~TempPotion() {}
