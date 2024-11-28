#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <vector>
#include "random.h"

class Map {
	private:
		struct layer {
			int indent;
			int length;
		};
		struct pattern {
			int position;
			std::vector<layer> layers;
			void create_layer(int w1, int h1, int w2, int h2);
		};
		int position_calculator(int x, int y);
		void add_pattern(pattern* pt, int orientation);
	public:
		int width;
		int height;
		std::vector<char> map;
		void generate();
		void print();
};

#endif
