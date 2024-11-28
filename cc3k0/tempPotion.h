#include "potiondecorator.h"

#ifndef TEMPPOTION_H
#define TEMPPOTION_H

class TempPotion : public PotionDecorator {
	int type;
	int effect;

	public:
		TempPotion(std::shared_ptr<PlayerStatus> ps, int type, int effect);
		virtual int getHP(int hp, int max_hp) const override;
		virtual int getATK(int atk) const override;
		virtual int getDEF(int def) const override;
		virtual std::string getState() const override;
		virtual ~TempPotion();
};

#endif
