#include "human.h"

Human::Human(int pos_x, int pos_y) : Player(140, 20, 20, pos_x, pos_y) {}

std::string Human::report(std::unique_ptr<Player>& p) {
	return "a Human";
}

double Human::calculateScore() {
	return gold * 1.5;
}

Human::~Human() {}
