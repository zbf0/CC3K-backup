#include "werewolf.h"
#include <string>

Werewolf::Werewolf(int pos_x, int pos_y) : Enemy{120, 30, 5, pos_x, pos_y, 'W'} {}

std::string Werewolf::report(std::unique_ptr<Player>& p) {
	std::string r = "a Werewolf(";
	r += std::to_string(hp) += ")";
	return r;
}

Werewolf::~Werewolf() {}
