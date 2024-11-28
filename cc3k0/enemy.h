#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "treasure.h"

class Player;

class Enemy : public Character {
	public:
		bool acted;
		bool compass_hold;
		int treasure_x;
		int treasure_y;
		Enemy(int hp, int atk, int def, int pos_x, int pos_y, char map_symbol, bool compass = false, int treasure_x = 0, int treasure_y = 0);
		std::vector<std::string> tick(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p) override;
		void refresh() override;
		virtual int takeHit(int aatk);
		std::vector<std::string> attackVisit(AttackVisitor* av) override;
		std::vector<std::string> die(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p) override;
		void print_map_symbol();
		void set_compass(bool compass) override;
		virtual ~Enemy() = 0;
	private:
		virtual bool hostile(std::unique_ptr<Player>& p);
		virtual std::string attack_ability(std::unique_ptr<Player>& p);
		virtual std::string passive_ability();
		virtual std::string die_ability(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap);
		virtual std::vector<int>* get_slot(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap);
};

#endif
