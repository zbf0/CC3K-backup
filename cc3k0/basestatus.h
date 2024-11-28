#ifndef BASESTATUS_H
#define BASESTATUS_H
#include "playerstatus.h"

class BaseStatus : public PlayerStatus {
	public:
		int getHP(int hp, int max_hp) const override;
		int getATK(int atk) const override;
		int getDEF(int def) const override;
		std::string getState() const override;
};

#endif
