#include "playerstatus.h"
#include "potiondecorator.h"

PotionDecorator::PotionDecorator(std::shared_ptr<PlayerStatus> playerStatus) : playerStatus{playerStatus} {}

std::string PotionDecorator::getState() const { return playerStatus->getState(); }

PotionDecorator::~PotionDecorator() { }
