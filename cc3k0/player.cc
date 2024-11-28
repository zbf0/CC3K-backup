#include "player.h"
#include "item.h"
#include "treasure.h"
#include "potion.h"
#include "barrier.h"
#include "itemvisitor.h"
#include "attackvisitor.h"
#include "enemy.h"
#include "tempPotion.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(int hp, int atk, int def, int pos_x, int pos_y) : Character(hp, hp, atk, def, 0, pos_x, pos_y, '@'), potionHistory{}, barrier{false}, compass{false}, merchant_hostile{false} {
	status = make_shared<BaseStatus>();
}

std::vector<std::string> Player::use(unique_ptr<Entity>& e) {
	ItemVisitor iv{this};
	return e->itemVisit(&iv);
}

std::vector<std::string> Player::useTreasure(Treasure* tr) {
	if (tr->isGuarded) {
		std::vector<std::string> report{"1", "Cannot collect gold that is currently guarded by a Dragon."};
		return report;
	}
	return gainGold(tr->size);
}

std::vector<std::string> Player::usePotion(Potion* pot) {
	std::string itemReport = "PC used ";
	// Potion logic
	status = make_shared<TempPotion>(status, pot->id, pot->id);
	switch (pot->id) {
		case 0:
			itemReport += "RH.";
			break;
		case 1:
			itemReport += "BA.";
			break;
		case 2:
			itemReport += "BD.";
			break;
		case 3:
			itemReport += "PH.";
			break;
		case 4:
			itemReport += "WA.";
			break;
		case 5:
			itemReport += "WD.";
			break;
		default:
			itemReport += "potion.";
	}
	std::vector<std::string> report{ "0", itemReport };
	return report;
}

std::vector<std::string> Player::useCompass(Compass* c) {
	compass = true;
	std::vector<std::string> report{ "0", "PC found the Compass." };
	return report;
}

std::vector<std::string> Player::useBarrierSuit(BarrierSuit* b) {
	if (b->isGuarded) {
		std::vector<std::string> report{ "1", "Cannot equip Barrier Suit that is currently guarded by a Dragon." };
		return report;
	}
	barrier = true;
	std::vector<std::string> report{ "0", "PC equipped the Barrier Suit." };
	return report;
}

void Player::clearEffects() {
	status = make_shared<BaseStatus>();
}

std::vector<std::string> Player::gainGold(int g) {
	std::string goldReport = "";
	if (g != 0) {
		goldReport = "PC gained " + std::to_string(g) + " gold.";
	}
	gold += g;
	std::vector<std::string> report{ "0", goldReport };
	return report;
}

std::vector<std::string> Player::attack(unique_ptr<Entity>& e) {
	AttackVisitor av{this};
	return e->attackVisit(&av);
}

std::vector<std::string> Player::attack(Enemy* e) {
	std::string attackReport = "";
	std::vector<std::string> report;
	int damage = e->takeHit(status->getATK(atk));
	if (damage >= 0) {
		attackReport += "PC deals " + std::to_string(damage) + " damage to "; 
		attackReport += e->map_symbol;
		attackReport += " (" + std::to_string(e->hp) + " HP).";
	} else {
		report.push_back("1");
		report.push_back("You can't attack that.");
		return report;
	}
	report.push_back("0");
	report.push_back(attackReport);
	return report;
}

int Player::takeHit(int eatk) {
	int damage = ceil((double)(100 * eatk)/(double)(100 + status->getDEF(def)));
	damage = (barrier)? ceil((double)damage / 2) : damage;
	hp = (hp - damage < 0)? 0 : hp - damage;
	if (status->getHP(hp, max_hp) == 0) die();
	return damage;
}

void Player::updatePos(int x, int y) {
	pos_x = x;
	pos_y = y;
}

void Player::die() {
	// death logic
}

double Player::calculateScore() {
	return gold;
}

Player::~Player() {}
