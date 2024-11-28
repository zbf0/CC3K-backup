#include "player.h"

#ifndef HUMAN_H
#define HUMAN_H

class Human : public Player {
	public:
		Human(int pos_x, int pos_y);
		std::string report(std::unique_ptr<Player>& p) override;
		double calculateScore() override;
		~Human() override;
};

#endif
