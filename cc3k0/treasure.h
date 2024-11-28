#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"
#include "itemvisitor.h"

class Treasure : public Item {
	public:
		int pos_x;
		int pos_y;
		int size;
		bool isGuarded;
		Treasure(int size, bool g = false, int x = 0, int y = 0);

		~Treasure() override;

		std::string report(std::unique_ptr<Player>& p) override;
		std::vector<std::string> itemVisit(ItemVisitor* iv) override;
		void print_map_symbol();
		void unguard() override;
};

#endif
