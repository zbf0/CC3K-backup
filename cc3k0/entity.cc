#include "entity.h"
#include "itemvisitor.h"
#include "attackvisitor.h"

Entity::Entity(int pos_x, int pos_y, char map_symbol) : pos_x{pos_x}, pos_y{pos_y}, map_symbol{map_symbol} {}

Entity::~Entity() {}

std::vector<std::string> Entity::itemVisit(ItemVisitor *iv) {
	//Left blank since nothing should happen unless this function is overriden
	std::vector<std::string> report{"-1", "That's not an item..."};
	return report;
}

std::vector<std::string> Entity::attackVisit(AttackVisitor *av) {
	std::vector<std::string> report{"-1", ""};
	return report;
}

std::vector<std::string> Entity::tick(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p){
	std::vector<std::string> report{"-1", ""};
	return report;
}

void Entity::refresh() {}



std::string Entity::report(std::unique_ptr<Player>& p) {
	return "";
}

void Entity::print_map_symbol() {
	std::cout << map_symbol;
}

std::vector<std::string> Entity::die(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p) {
	std::vector<std::string> report{"0", "It's dead!"};
	return report;
}

void Entity::set_compass(bool compass) {}

void Entity::unguard() {}
