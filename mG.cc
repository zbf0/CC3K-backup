#include "mapGenerator.h"

void Map::pattern::create_layer(int w1, int h1, int w2, int h2, bool notch = false) {
	for (int i = 0; i < h1; ++i) {
		layers.push_back({0,w1});
	}
	for (int i = 0; i < h2; ++i) {
		layers.push_back({0,w2});
	}
}


int Map::position_calculator(int w, int h) {
	return width * h + w;
}

void Map::add_pattern(pattern* pt, int orientation) {
	int iterator_w = 1;
	int iterator_h = 1;
	if (orientation == 1) {
		iterator_w = -1;
	} else if (orientation == 2) {
		iterator_h = -1;
	} else if (orientation == 3) {
		iterator_w = -1;
		iterator_h = -1;
	}
	int pos = pt->position;
	for (auto l : pt->layers) {
		for (int i = 0; i < l.length; ++i) {
			map[pos + iterator_w * (l.indent + i)] = '.';
		}
		pos += iterator_h * width;
	}
}

void Map::generate() {
	std::vector<int> *random = randomIntGenerator(0, 99, 20, true);
	// determine position of 4 side patterns
	(*random)[0] = position_calculator(1 + 2 * random->at(0) / 100 , 1 + 2 * random->at(1) / 100);
	(*random)[1] = position_calculator(width - 1 - 1 - 2 * random->at(2) / 100 , 1 + 2 * random->at(3) / 100);
	(*random)[2] = position_calculator(1 + 2 * random->at(4) / 100 , height - 1 - 1 - 2 * random->at(5) / 100);
	(*random)[3] = position_calculator(width - 1 - 1 - 2 * random->at(6) / 100 , height - 1 - 1 - 2 * random->at(7) / 100);
	// determine the gap between 4 side patterns
	for (int i = 8; i < 12; ++i) {
		if (random->at(i) < 30) {
			(*random)[i] = 0;
		} else if (random->at(i) > 70) {
			(*random)[i] = 99;
		}
	}
	for (int i = 12; i < 16; ++i) {
		if (random->at(i - 4) < 50) {
			(*random)[i] = 100 - random->at(i - 4) - 20 - 10 * random->at(i + 4) / 100;
		} else {
			int temp = random->at(i - 4);
			(*random)[i - 4] = random->at(i - 4) - 20 - 10 * random->at(i + 4) / 100;
			(*random)[i] = 100 - temp;
		}
	}
	for (int i : {8, 9, 12, 13}) {
		(*random)[i] = width / 5 + width / 2 * random->at(i) / 100;
	}
	for (int i : {10, 11, 14, 15}) {
		(*random)[i] = height / 2 * random->at(i) / 100;
	}
	// ensure the gap is huge enough
	if (random->at(8) + random->at(12) + 4 >= width) {
		(*random)[8] -= 1;
		(*random)[12] -= 2;
	}
	if (random->at(9) + random->at(13) + 4 >= width) {
		(*random)[9] -= 1;
		(*random)[13] -= 2;
	}
	if (random->at(10) + random->at(14) + 4 >= height / 2) {
		(*random)[10] -= 1;
		(*random)[14] -= 2;
	}
	if (random->at(11) + random->at(15) + 4 >= height / 2) {
		(*random)[11] -= 1;
		(*random)[15] -= 2;
	}
	// create a vector s pattern
	std::vector<pattern*> patterns;
	for (int i = 0; i < 4; ++i) {
		pattern *p = new pattern;
		p->position = random->at(i);
		patterns.push_back(p);
	}
	// add 4 side patterns
	patterns[0]->create_layer(random->at(8), height / 5, width / 5, random->at(10));
	patterns[1]->create_layer(random->at(12), height / 5, width / 5, random->at(11));
	patterns[2]->create_layer(random->at(9), height / 5, width / 5, random->at(14));
	patterns[3]->create_layer(random->at(13), height / 5, width / 5, random->at(15));
	
	// create the fifth (middle) pattern
	// determine 4 edge of the final pattern
	(*random)[16] = width / 5 + 5 + width / 15 * random->at(16) / 100;
	(*random)[17] = width / 5 + 5 + width / 15 * random->at(17) / 100;
	(*random)[18] = height / 5 + 5 + height / 15 * random->at(18) / 100;
	(*random)[19] = height / 5 + 5 + height / 15 * random->at(19) / 100;
	// modify to avoid being too long
	if (width - random->at(16) - random->at(17) >  height - random->at(18) - random->at(19)) {
		(*random)[16] += (width / 2 - random->at(16)) * (random->at(5) + 50) / 200;
		(*random)[17] += (width / 2 - random->at(17)) * (random->at(6) + 50) / 200;
		
	} else if (width - random->at(16) - random->at(17) <  height - random->at(18) - random->at(19)) {
		(*random)[18] += (height / 2 - random->at(18)) / 2;
		(*random)[19] += (height / 2 - random->at(19)) / 2;
	}
	patterns.push_back(new pattern);
	patterns[4]->position = position_calculator(random->at(16), random->at(18));
	patterns[4]->create_layer(width - random->at(16) - random->at(17), height - random->at(18) - random->at(19) , 0, 0);
	
	// add all patterns to map
	for (int i = 0; i < width * height; ++i) {
		map.push_back(' ');
	}
	for (int i = 0; i < 5; ++i) {
		add_pattern(patterns[i], i);
	}
	// delete all
	for (int i = 0; i < 5; ++i) {
		delete patterns[i];
	}
	delete random;
}

void Map::print() {
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			std::cout << map.at(w + h * width);
		}
		std::cout << std::endl;
	}
}
