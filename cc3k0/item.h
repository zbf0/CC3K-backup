#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "itemvisitor.h"

class ItemVisitor;

class Item : public Entity {
	public:
		Item(char map_symbol);
		virtual void print_map_symbol();
		virtual ~Item() = 0;
};

#endif

