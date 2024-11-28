#ifndef POTION_H
#define POTION_H

#include "item.h"
#include "itemvisitor.h"


class Potion : public Item {
	public:
		int id; //0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD
		Potion(int id);
		~Potion() override;
		std::string report(std::unique_ptr<Player>& p) override;
		std::vector<std::string> itemVisit(ItemVisitor* iv) override;

};

#endif
