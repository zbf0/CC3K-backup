#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "basestatus.h"

#include <math.h>
#include <iostream>


//Forward declaration is necessary to prevent compiler shenanigans. (Including item would include itemvisitor or something and itemvisitor needs player
//to be defined but it hasn't been defined yet since we are right here
class Item;
class Potion;
class Treasure;
class Compass;
class Enemy;
class BarrierSuit;

class Player : public Character {
	protected:
		std::vector<int> potionHistory;
	public:
		bool barrier;
		bool compass;
		bool merchant_hostile;
		std::shared_ptr<PlayerStatus> status;
		Player(int hp, int atk, int def, int pos_x, int pos_y);
		std::vector<std::string> use(std::unique_ptr<Entity>& e);

		// usePotion and useTreasure are called in ItemVisitor via double dispatch shenanigans. Overriding these for race abilities is fine
		virtual std::vector<std::string> usePotion(Potion* pot);
		virtual std::vector<std::string> useTreasure(Treasure* tr);
		virtual std::vector<std::string> useCompass(Compass* c);
		virtual std::vector<std::string> useBarrierSuit(BarrierSuit* b);
		virtual std::vector<std::string> gainGold(int g); //Different from useTreasure() since the gold you gain from killing enemies is not an item but is still doubled from race abilities
		void updatePos(int x, int y);// pos+x amd pos_y are private and i don't want to make them public so player has this exclusive command
		std::vector<std::string> attack(std::unique_ptr<Entity>& e);
		std::vector<std::string> attack(Enemy* e);
		int takeHit(int eatk);
		void clearEffects();
		void die();
		virtual double calculateScore();
		virtual ~Player() = 0;
};

#endif
