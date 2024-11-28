#include "character.h"

Character::Character(int hp, int max_hp, int atk, int def, int gold, int pos_x, int pos_y, char map_symbol) : Entity{pos_x, pos_y, map_symbol}, hp{hp}, max_hp{max_hp}, atk{atk}, def{def}, gold{gold} {}

void Character::set_compass(bool compass) {}

Character::~Character() {}
