#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <memory>

class ItemVisitor;
class AttackVisitor;
class Player;

class Entity {
	public:
		int pos_x;
		int pos_y;
		char map_symbol;

		Entity(int pos_x, int pos_y, char map_symbol);
		virtual std::vector<std::string> itemVisit(ItemVisitor* iv);
		virtual std::vector<std::string> attackVisit(AttackVisitor* av);
		virtual ~Entity() = 0;
		virtual std::vector<std::string> tick(std::vector<std::vector<char>>* floormap, std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p);
		virtual void refresh();
		virtual std::string report(std::unique_ptr<Player>& p) = 0; //Returns name of entity and amount of HP if it's an enemy
		virtual void print_map_symbol();
		virtual std::vector<std::string> die(std::vector<std::vector<std::unique_ptr<Entity>>>* entitymap, std::unique_ptr<Player>& p);
		virtual void set_compass(bool compass);
		virtual void unguard();
};

#endif
