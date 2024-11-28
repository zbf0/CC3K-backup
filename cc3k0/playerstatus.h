#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include <string>

class PlayerStatus {
	public:
		virtual int getHP(int hp, int max_hp) const = 0;
		virtual int getATK(int atk) const = 0;
		virtual int getDEF(int def) const = 0;
		virtual std::string getState() const = 0;
		virtual ~PlayerStatus();
};

#endif
		
