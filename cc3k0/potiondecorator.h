#ifndef POTIONDECORATOR_H
#define POTIONDECORATOR_H
#include "playerstatus.h"
#include <memory>

class PotionDecorator : public PlayerStatus {
	protected:
		std::shared_ptr<PlayerStatus> playerStatus;
	public:
		PotionDecorator(std::shared_ptr<PlayerStatus> playerstatus);
		virtual int getHP(int hp, int max_hp) const = 0;
		virtual int getATK(int atk) const = 0;
		virtual int getDEF(int def) const = 0;
		virtual std::string getState() const override;
		virtual ~PotionDecorator();
};

#endif
