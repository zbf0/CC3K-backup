#include "enemy.h"
#include "attackvisitor.h"
#include "coorddiff.h"
#include "player.h"
#include "random.h"
#include "compass.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

Enemy::Enemy(int hp, int atk, int def, int pos_x, int pos_y, char map_symbol, bool compass, int treasure_x, int treasure_y) : Character{hp, hp, atk, def, 1, pos_x, pos_y, map_symbol}, acted{false}, compass_hold{compass}, treasure_x{treasure_x}, treasure_y{treasure_y} {}

Enemy::~Enemy() {}

bool Enemy::hostile(unique_ptr<Player>& p) {
	return true;
}

std::string Enemy::attack_ability(std::unique_ptr<Player>& p) {
	// no special ability by default
	return "";
}

std::string Enemy::passive_ability() {
	// no special ability by default
	return "";
}

std::string Enemy::die_ability(std::vector<std::vector<unique_ptr<Entity>>>* entitymap) {
	// no special ability by default
	return "";
}

vector<int>* Enemy::get_slot(std::vector<std::vector<char>>* floormap, std::vector<std::vector<unique_ptr<Entity>>>* entitymap) {
	vector<int>* available_slot = new vector<int>;
	int i = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if ((x || y) && (*floormap)[pos_x + x][pos_y + y] == '.' && (*entitymap)[pos_x + x][pos_y + y] == nullptr) {
				available_slot->push_back(i);
			}
			++i;
		}
	}
	return available_slot;
}

std::vector<std::string> Enemy::tick(std::vector<std::vector<char>>* floormap, std::vector<std::vector<unique_ptr<Entity>>>* entitymap, unique_ptr<Player>& p){ 
	std::string action = "";
	std::string abilityReport = "";
	std::vector<std::string> report;
	if (!acted) {
		// cout << report() << " at " << pos_x << " " << pos_y << " attempting to tick" << endl;
		// cout << p->pos_x << p->pos_y;
		if (hostile(p) && pos_x <= p->pos_x + 1 && pos_x >= p->pos_x - 1 && pos_y <= p->pos_y + 1 && pos_y >= p->pos_y - 1) {
			vector<int>* random = randomIntGenerator(0, 1);
			int hitchance = random->at(0);
			delete random;
			// cout << "attempting attack, rolled a " << hitchance << endl;
			action += " ";
			action += map_symbol;
			action += " (" + std::to_string(hp) + " HP)";
			if (hitchance == 1) {
				std::string damage = std::to_string(p->takeHit(atk));
				action += " deals " + damage + " damage to PC.";
				abilityReport = attack_ability(p);
				if (abilityReport != "") action += " " + abilityReport;
				if (p->status->getHP(p->hp, p->max_hp) < 1) {
					p->die();
					std::string deathReport = "\nPC was slain by ";
					deathReport += map_symbol;
					deathReport += " (" + std::to_string(hp) + " HP).";
					
					report.push_back("X");
					report.push_back(action + deathReport);
					return report;
				}
			} else {
			        action += " tries to attack and whiffs.";
			}
		} else {
			// cout << "attempting movement" << endl;
			vector<int>* available_slot = get_slot(floormap, entitymap);
			if (available_slot->size()) {
				randomSort(*available_slot);
				int tx = pos_x - 1 + available_slot->at(0) % 3;
				int ty = pos_y - 1 + available_slot->at(0) / 3;
				entitymap->at(tx)[ty] = std::move(entitymap->at(pos_x)[pos_y]);
				entitymap->at(pos_x)[pos_y] = nullptr;
				pos_x = tx;
				pos_y = ty;
			}
			delete available_slot;
		}
		abilityReport = passive_ability();
		if (abilityReport != "") action += " " + abilityReport;
		acted = true;
	}

	report.push_back("0");
	report.push_back(action);
	return report;
}

void Enemy::refresh() {
	acted = false;
}

int Enemy::takeHit(int aatk) {
	int damage = ceil((double)(100 * aatk)/(double)(100 + def));
	//cout << "You dealt " << damage << " damage" << endl;
	hp = (hp - damage < 0)? 0 : hp - damage;
	return damage;
}


std::vector<std::string> Enemy::attackVisit(AttackVisitor* av) {
	return av->visit(this);
}

std::vector<std::string> Enemy::die(std::vector<std::vector<unique_ptr<Entity>>>* entitymap, unique_ptr<Player>& p) {
	if (compass_hold) {
		entitymap->at(pos_x)[pos_y] = std::move(make_unique<Compass>(pos_x,pos_y));
	} 
	std::string deathReport = die_ability(entitymap);
	std::string defaultReport = "";
	defaultReport += map_symbol;
	defaultReport += " (" + std::to_string(hp) + " HP) was defeated.";
	// Player receives gold for defeating enemy
	std::string goldReport = p->gainGold(gold)[1];
	if (goldReport != "") defaultReport += " " + goldReport;
	if (deathReport != "") defaultReport += " " + deathReport;
	std::vector<std::string> report{"0", defaultReport};

	return report;
}

void Enemy::set_compass(bool compass) {
	compass_hold = compass;
}

void Enemy::print_map_symbol() {
	std::cout << "\033[31m" << map_symbol << "\033[0m";
}
