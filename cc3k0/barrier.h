#ifndef BARRIER_H
#define BARRIER_H

#include "item.h"
#include "itemvisitor.h"

class BarrierSuit : public Item {
	public:
		int pos_x;
		int pos_y;
		bool isGuarded;

		BarrierSuit(bool g = false, int x = 0, int y = 0);
		~BarrierSuit() override;

		std::string report(std::unique_ptr<Player>& p) override;
		std::vector<std::string> itemVisit(ItemVisitor* iv) override;
		void unguard() override;
};

#endif
