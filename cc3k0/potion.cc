#include "potion.h"

Potion::Potion(int id) : Item{'P'}, id{id} {}

Potion::~Potion() {}

std::string Potion::report(std::unique_ptr<Player>& p) {
	if (p->status->getState().find(std::to_string(id)) == std::string::npos) {
		return "an Unknown potion";
	}

	switch(id) {
		case 0:
			return "a RH potion";
			break;
		case 1:
			return "a BA potion";
			break;
		case 2:
			return "a BD potion";
			break;
		case 3:
			return "a PH potion";
			break;
		case 4:
			return "a WA potion";
			break;
		case 5:
			return "a WD potion";
			break;
		default:
			return "an Unknown potion";
			break;
	}
}

std::vector<std::string> Potion::itemVisit(ItemVisitor* iv) {
	return iv->visit(this);
}
