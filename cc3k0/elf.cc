#include "elf.h"
#include "potion.h"
#include "tempPotion.h"
#include <iostream>
#include <memory>

Elf::Elf(int pos_x, int pos_y) : Player(140, 30, 10, pos_x, pos_y) {}

std::vector<std::string> Elf::usePotion(Potion* pot) {
	std::string itemReport = "PC used ";
	int effect = pot->id % 3;
	status = std::make_shared<TempPotion>(status, pot->id, effect);
	switch (pot->id) {
		case 0:
			itemReport += "RH.";
			break;
		case 1:
			itemReport += "BA.";
			break;
		case 2:
                        itemReport += "BD.";
			break;
                case 3:
                        itemReport += "PH.";
			break;
                case 4:
			itemReport += "WA.";
			break;
  		case 5:
                        itemReport += "WD.";
			break;
	        default:
                        itemReport += "potion.";
	}
	std::vector<std::string> report{"0", itemReport};
	return report;
}

std::string Elf::report(std::unique_ptr<Player>& p) {
	return "an Elf";
}

Elf::~Elf() {}
