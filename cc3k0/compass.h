#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"
#include "itemvisitor.h"

class Compass : public Item {
	public:
		int pos_x;
		int pos_y;
		Compass(int x = 0, int y = 0);

		~Compass() override;

		std::string report(std::unique_ptr<Player>& p) override;
		std::vector<std::string> itemVisit(ItemVisitor* iv) override;
		void print_map_symbol();
};

#endif
