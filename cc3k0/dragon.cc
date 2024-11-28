#include "dragon.h"
#include <string>

Dragon::Dragon(int pos_x, int pos_y, int treasure_x, int treasure_y) : Enemy{150, 20, 20, pos_x, pos_y, 'D', false, treasure_x, treasure_y} {
	gold = 0;
}

std::string Dragon::report(std::unique_ptr<Player>& p) {
        std::string r = "a Dragon(";
        r += std::to_string(hp) += ")";
        return r;
}

Dragon::~Dragon() {}

bool Dragon::hostile(std::unique_ptr<Player>& p) {
	int x_diff = p->pos_x - treasure_x;
	int y_diff = p->pos_y - treasure_y;
	if (-1 <= x_diff && x_diff <= 1 && -1 <= y_diff && y_diff <= 1) {
		return true;
	} else {
		return false;
	}
}

std::string Dragon::die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) {
	entitymap->at(treasure_x)[treasure_y]->unguard();
	return "Its hoard is no longer protected.";
}

std::vector<int>* Dragon::get_slot(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap) {
	
	//std::cout << treaure_x << ' ' << treasure_y << std::endl;
	
	std::vector<int>* available_slot = new std::vector<int>;
	return available_slot;
}
