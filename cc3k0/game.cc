#include "game.h"
#include "random.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "merchant.h"
#include "dragon.h"
#include "treasure.h"
#include "potion.h"
#include "coorddiff.h"
#include "compass.h"
#include "barrier.h"


#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>

using namespace std;


// Open to the possibility of open room size later
Game::Game(string race) : floor{1}, width{79}, height{25}, maxFloor{5}, px{0}, py{0} {
	vector<vector<char>> f (79, vector<char> (25, ' '));
	floormap = f;
      	vector<vector<unique_ptr<Entity>>> e;
	e.resize(width);
	for (int x = 0; x < width; x++) {
		e[x].resize(height);
		for (int y =  0; y < height; y++) {
			e[x][y] = nullptr;
		}
	}
	entitymap = std::move(e);

	if (race == "e") {
		p = make_unique<Elf>(0,0);
	} else if (race == "d") {
		p = make_unique<Dwarf>(0,0);
	} else if (race == "o") {
		p = make_unique<Orc>(0,0);
	} else {
		p = make_unique<Human>(0,0);
	}

	vector<vector<char>> r;
	r.resize(maxFloor);
	rare_entities = r;
	initRareEntities();
}

Game::~Game() {}

void Game::read_maps(string file) {

	ifstream fs(file);
	vector<vector<char>> map;

	map.resize(width);
	for (int i = 0; i < width; i++) {
		map[i].resize(height);
	}

	for (int i = 0; i < 5; ++i) {
		maps.push_back(map);
	}

	for (int i = 0; i < 5; ++i) {
		string line;
		char here = ' ';
		int x = 0;
		int y = 0;
		for (int j = 0; j < 25; ++j) {
			getline(fs, line);
			istringstream ss(line);
			while (ss >> noskipws >> here) {
				maps[i][x][y] = here;
				x++;
			}
			x = 0;
			y ++;
		}
	}
}

/*std::vector<std::vector<char>>* Game::get_map(int floor) {
	int ms = maps.size();
	if (floor <= ms) {
		return &maps[floor - 1];
	} else {
		return nullptr;
	}
}*/

void Game::initRareEntities() {
	// Barrier suit
	int bsFloor = randomIntGenerator(1, maxFloor)->at(0);
	rare_entities[bsFloor - 1].push_back('B');
}
/*
void Game::map_load(string file) {
	ifstream fs(file);
	string line;
	int x = 0;
	int y = 0;
	vector<vector<char>> map;
	char here = ' ';

	map.resize(width);

	for (int i = 0; i < width; i++) {
		map[i].resize(height);
	}


	while (getline(fs, line)) {
		istringstream ss(line);
		while (ss >> noskipws >> here) {
			map[x][y] = here;
			x++;
		}
		x = 0;
		y ++;
	}
	map_load(map);

}*/


// Loads in a map according to the symbols on page 10 of the outline
// Can add new concrete entities onto the switch statement as they get implemented
void Game::map_load (vector<vector<char>>& map) {
	char here = ' ';

	vector<vector<unique_ptr<Entity>>> e;
        e.resize(width);
        for (int x = 0; x < width; x++) {
                e[x].resize(height);
                for (int y =  0; y < height; y++) {
                        e[x][y] = nullptr;
                }
        }
        entitymap = std::move(e);



	struct dragon_hoard {
		int x;
		int y;
	};

	struct enemy_pos {
		int x;
		int y;
	};

	vector<dragon_hoard> dragon_hoard_store;
	vector<enemy_pos> compassable_enemies;


	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			here = map[x][y];
			switch(here) {
				case '|':
				case '-':
				case '+':
				case '\\':
				case ' ':
				case '#':
					floormap[x][y] = here;
				break;
				default:
					floormap[x][y] = '.';
				break;

			}
			switch (here) {
				case '@':
					px = x;
					py = y;
					p->updatePos(x, y);
				break;
				case 'V':
					entitymap[x][y] = std::move(make_unique<Vampire>(x,y));
					compassable_enemies.push_back({x,y});
				break;
				case 'W':
					entitymap[x][y] = std::move(make_unique<Werewolf>(x,y));
					compassable_enemies.push_back({x,y});
				break;
				case 'N':
					entitymap[x][y] = std::move(make_unique<Goblin>(x,y));
					compassable_enemies.push_back({x,y});
				break;
				case 'T':
					entitymap[x][y] = std::move(make_unique<Troll>(x,y));
					compassable_enemies.push_back({x,y});
				break;
				case 'X':
					entitymap[x][y] = std::move(make_unique<Phoenix>(x,y));
				break;
				case 'M':
					entitymap[x][y] = std::move(make_unique<Merchant>(x,y));
				break;
				case 'D':
					entitymap[x][y] = std::move(make_unique<Dragon>(x,y));
				break;
				case '0':
					entitymap[x][y] = std::move(make_unique<Potion>(0));
				break;
				case '1':
					entitymap[x][y] = std::move(make_unique<Potion>(1));
				break;
				case '2':
					entitymap[x][y] = std::move(make_unique<Potion>(2));
				break;
				case '3':
					entitymap[x][y] = std::move(make_unique<Potion>(3));
				break;
				case '4':
					entitymap[x][y] = std::move(make_unique<Potion>(4));
				break;
				case '5':
					entitymap[x][y] = std::move(make_unique<Potion>(5));
				break;
				case '6':
					entitymap[x][y] = std::move(make_unique<Treasure>(1));
				break;		
				case '7':
					entitymap[x][y] = std::move(make_unique<Treasure>(2));
				break;
				case '8':
					entitymap[x][y] = std::move(make_unique<Treasure>(4));
				break;
				case '9':
					entitymap[x][y] = std::move(make_unique<Treasure>(6, true, x, y));
					dragon_hoard_store.push_back({x,y});
				break;
				case 'B':
					entitymap[x][y] = std::move(make_unique<BarrierSuit>(true, x, y));
					dragon_hoard_store.push_back({x,y});
				break;
			}
		}
	}
	for (dragon_hoard d : dragon_hoard_store) {
		for (int yd = -1; yd <= 1; ++yd) {
			for (int xd = -1; xd <= 1; ++xd) {
				if (entitymap[d.x + xd][d.y + yd] && entitymap[d.x + xd][d.y + yd]->map_symbol == 'D') {
					entitymap[d.x + xd][d.y + yd] = std::move(make_unique<Dragon>(d.x + xd, d.y + yd, d.x, d.y));
					break;
					break;
				}
			}
		}
	}
	
	int ces = compassable_enemies.size();
	if (ces) {
		vector<int>* random = randomIntGenerator(0, ces - 1);
		int i = random->at(0);
		enemy_pos c = compassable_enemies[i];
		entitymap[c.x][c.y]->set_compass(true);
		delete random;
	} else {
		p->compass = true;
	}
}

struct layer {
	int indent;
	int length;
};

struct pattern {
	int x;
	int y;
	int size;
	std::vector<layer> layers;
	std::vector<char> entities;
	pattern(int x, int y, int size, std::vector<layer> layers) : x{x}, y{y}, size{size}, layers{layers} {}
};


// initialize the map
void map_initialize(vector<vector<char>>& map) {
	map.clear();
	vector<string> lines {
		"|-----------------------------------------------------------------------------|",
		"|                                                                             |",
		"| |--------------------------|        |-----------------------|               |",
		"| |..........................|        |.......................|               |",
		"| |..........................+########+.......................|-------|       |",
		"| |..........................|   #    |...............................|--|    |",
		"| |..........................|   #    |..................................|--| |",
		"| |----------+---------------|   #    |----+----------------|...............| |",
		"|            #                 #############                |...............| |",
		"|            #                 #     |-----+------|         |...............| |",
		"|            #                 #     |............|         |...............| |",
		"|            ###################     |............|   ######+...............| |",
		"|            #                 #     |............|   #     |...............| |",
		"|            #                 #     |-----+------|   #     |--------+------| |",
		"|  |---------+-----------|     #           #          #              #        |",
		"|  |.....................|     #           #          #         |----+------| |",
		"|  |.....................|     ########################         |...........| |",
		"|  |.....................|     #           #                    |...........| |",
		"|  |.....................|     #    |------+--------------------|...........| |",
		"|  |.....................|     #    |.......................................| |",
		"|  |.....................+##########+.......................................| |",
		"|  |.....................|          |.......................................| |",
		"|  |---------------------|          |---------------------------------------| |",
		"|                                                                             |",
		"|-----------------------------------------------------------------------------|"};
	for (string s : lines){
		std::vector<char> v(s.begin(), s.end());
		map.push_back(v);
	}
}

// generate a string, each char denote an entity that will be spawned
string spawn_entity_list() {
	string spawn_entity_list = "@\\";
	vector<int>* random;
	
	random = randomIntGenerator(0,89,10,true);
	for (int i : *random) {
		spawn_entity_list += to_string(i % 6);
	}
	delete random;

	int dragons = 0;
	random = randomIntGenerator(0,95,10,true);
	for (int i : *random) {
		if (i % 8 <= 4) {
			spawn_entity_list += to_string(6);
		} else if (i % 8 == 5) {
			spawn_entity_list += to_string(9);
			++dragons;
		} else {
			spawn_entity_list += to_string(7);
		}
	}
	delete random;

	random = randomIntGenerator(0,19 - dragons);
	int compass_holder = random->at(0) + spawn_entity_list.length();
	delete random;

	random = randomIntGenerator(0,179,20 - dragons,true);
	for (int i : *random) {
		if (i % 18 <= 3) {
			spawn_entity_list += 'W';
		} else if (i % 18 <= 6) {
			spawn_entity_list += 'V';
		} else if (i % 18 <= 11) {
			spawn_entity_list += 'N';
		} else if (i % 18 <= 13) {
			spawn_entity_list += 'T';
		} else if (i % 18 <= 15) {
			spawn_entity_list += 'X';
		} else {
			spawn_entity_list += 'M';
		}
	}
	delete random;

	spawn_entity_list[compass_holder] = tolower(spawn_entity_list[compass_holder]);
	return spawn_entity_list;
}

void pattern_chooser(string entities, vector<pattern*> patterns) {
	int ne = entities.length(); // number of entities
	vector<int>* chooser = randomIntGenerator(0,4,2);
	vector<int>* c = randomIntGenerator(0,99,ne - 2,true);
	chooser->insert(chooser->end(), c->begin(), c->end());

	for (int i = 0; i < ne; ++i) {
		patterns[chooser->at(i) % 5]->entities.push_back(entities[i]);
		if (entities[i] == '9' || entities[i] == 'B') {
			patterns[chooser->at(i) % 5]->entities.push_back('D');
		}
	}
	delete chooser;
}

// create entity to map
bool entity_create(vector<vector<char>>& map, pattern p, int index, char entity) {
	int x = p.x;
	int y = p.y;
	for (layer l : p.layers) {
		if (index > l.length - 1) {
			index -= l.length;
		} else {
			x += (l.indent + index);
			break;
		}
		++y;
	}
	if (map.at(y).at(x) != '.') {
		return false;
	} else if (entity == '9' || entity == 'B') {
		vector<int> dragon_slot;
		for (int dy = -1; dy <= 1; ++dy) {
			for (int dx = -1; dx <= 1; ++dx) {
				if ((dy || dx) && map.at(y + dy).at(x + dx) == '.') {
					dragon_slot.push_back(3 * (dy + 1) + (dx + 1));
				}
			}
		}
		if (dragon_slot.size()) {
			randomSort(dragon_slot);
			int nx = x - 1 + dragon_slot[0] % 3;
			int ny = y - 1 + dragon_slot[0] / 3;
			map.at(ny).at(nx) = 'D';
		}
		map.at(y).at(x) = entity;
	} else {
		map.at(y).at(x) = entity;
	}
	return true;
}

// choose a tile to spawn an entity, then call entity_create()
void tile_chooser(vector<vector<char>>& map, pattern p) {
	int ne = p.entities.size(); // number of entities
	vector<int>* chooser = randomIntGenerator(0,p.size - 1,ne,false, false);
	int ri = 0;
	int ei = 0;
	while (true) {
		if (p.entities.at(ei) == 'D') {
			++ei;
		} else if (entity_create(map, p, chooser->at(ri), p.entities[ei])) {
			++ri;
			++ei;
		} else {
			++ri;
		}
		if (ei >= ne) {
			break;
		}
	}
	delete chooser;
}

// generate the map
void map_generate(vector<vector<char>>& map, vector<char>& rare_entities) {
	map_initialize(map);

	pattern p1 = pattern{3,3,104,{{0,26},{0,26},{0,26},{0,26}}};
	pattern p2 = pattern{39,3,201,{{0,23},{0,23},{0,31},{0,34},{22,15},{22,15},{22,15},{22,15},{22,15},{22,15}}};
	pattern p3 = pattern{38,10,36,{{0,12},{0,12},{0,12}}};
	pattern p4 = pattern{4,15,147,{{0,21},{0,21},{0,21},{0,21},{0,21},{0,21},{0,21}}};
	pattern p5 = pattern{37,16,150,{{28,11},{28,11},{28,11},{0,39},{0,39},{0,39}}};

	string entities = spawn_entity_list();

	int r = rare_entities.size();
	for (int i = 0; i < r; ++i) entities += rare_entities[i];

	pattern_chooser(entities, {&p1,&p2,&p3,&p4,&p5});
	
	for (pattern p : {p1,p2,p3,p4,p5}) {
		tile_chooser(map, p);
	}
}

// map_generate() ends here

void Game::map_generate_test() {
	vector<vector<char>> map;
	map_generate(map, rare_entities[floor - 1]);
	for (vector<char> l : map) {
		for (char c : l) {
			cout << c;
		}
		cout << endl;
	}
}

void Game::map_load() {
	vector<vector<char>> map;
	map_generate(map, rare_entities[floor - 1]);

	vector<vector<char>> map_correct; //map_generate produces a map with the axes flipped. This corrects it

	map_correct.resize(width);
	for (int x = 0; x < width; x++) {
		map_correct[x].resize(height);
		for (int y = 0; y < height; y++) {
			map_correct[x][y] = map[y][x];
		}
	}
	map_load(map_correct);
}

void Game::map_load(int floor) {
	int ms = maps.size();
	if (floor <= ms) {
		map_load(maps.at(floor - 1));
	} else {
		map_load();
	}
}

void Game::newFloor() {
	floor++;
	map_load(floor);
	//New floor logic. Make sure to update player's internal x_pos y+pos as well as game's px and py
}

bool Game::endGame(string finalReport) {
	double score = p->calculateScore();
	print_status();
	cout << finalReport << endl << endl;

	if (p->status->getHP(p->hp, p->max_hp) < 1) {
		cout << "You have died." << endl;
	} else {
		cout << "Congratulations! You have beaten CC3K+!" << endl;
	}

	cout << "Your final score is: " << score << endl;
	cout << "Would you like to play again? (y/n)" << endl;
	string input;
	while (cin >> input) {
		if (input == "y" || input == "Y") {
			return true;
		} else if (input == "n" || input == "N") {
			return false;
		} else if (input == "r") {
			return true;
		} else if (input == "q") {
			return false;
		} else {
			cout << endl << "\033[1;31mInvalid input.\033[0m" << endl;
			cout << "Would you like to play again? (y/n)" << endl;
		}
	}
	return false;
}

// Should include a stair hidng mechanic when we implement compass
void Game::map_print() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (x == px && y == py) {
				cout << "\033[35m@\033[0m";
			} else if (entitymap[x][y]) {
				entitymap[x][y]->print_map_symbol();
			} else if (floormap[x][y] == '\\') {
				if (p->compass) {
					cout << "\033[32m" << '\\' << "\033[0m";
				} else {
					cout << '.';
				}
			} else {
				if (!p->compass && floormap[x][y] == '\\') {
					cout << '.';
				} else {
					cout << floormap[x][y];
				}
			}
		}
		cout << endl;
	}
}

void Game::print_status() {
	map_print();
	std::string s = "Race: " + p->report(p).substr(p->report(p).find(" ") + 1) + " Gold: " + std::to_string(p->gold);
        cout << s;
	cout << setw(79 - s.size() - 1) << right << "Floor " << floor << endl;
        cout << "HP: " << p->status->getHP(p->hp, p->max_hp) << endl;
        cout << "Atk: " << p->status->getATK(p->atk) << endl;
        cout << "Def: " << p->status->getDEF(p->def) << endl;
	cout << "Action: ";
}

vector<string> Game::update() {
	vector<string> actionReport;
	string actionString = "";
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (entitymap[x][y]) {
				std::vector<std::string> tickReport = entitymap[x][y]->tick(&floormap, &entitymap, p);
				if (tickReport[1] != "") actionString += "\n" + tickReport[1].substr(1);
				if (tickReport[0] == "X") {
					actionReport.push_back(actionString);
					return actionReport;
				}
			}
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (entitymap[x][y]) {
				entitymap[x][y]->refresh();
			}
		}
	}
	actionReport.push_back(actionString);
	
	print_status();
	string observeString = "";
	// All this code just to make entities in a 1 range radius use report() in a grammatically sound way
	vector<int> v = {0, 0};
	int count = 0;
	for (int i = 1; i < 10; i++) {
		v = getCoordDiff(i);
		int tx = px + v[0];
		int ty = py + v[1];
		if (entitymap[tx][ty]) {
			count++;
		}
	}

	if (count > 0) {
		for (int i = 1; i < 10; i++) {
			v = getCoordDiff(i);
			int tx = px + v[0];
			int ty = py + v[1];
			if (entitymap[tx][ty]) {
				observeString += entitymap[tx][ty]->report(p);
				count--;
				if (count > 1) {
					observeString += ", ";
				} else if (count == 1) {
					observeString += ", and ";
				} else {
					observeString += ".";
				}
			}
			
		}
	}

	actionReport.push_back(observeString);
	return actionReport;
}

vector<string> Game::move (int direction) {
	int tx = px;
	int ty = py;
	//Doesn't check if target location will be out of bounds since you can't exist on the border
	vector<int> v = getCoordDiff(direction);
	tx += v[0];
	ty += v[1];

	vector<string> moveReport;
	char target = floormap[tx][ty];
	if ((target == '.' || target == '+' || target == '#') && !entitymap[tx][ty]) {
		px = tx;
		py = ty;
		p->updatePos(px, py);
		moveReport.push_back("0");
		moveReport.push_back("");
	} else if (entitymap[tx][ty] && (entitymap[tx][ty]->map_symbol == 'G' || entitymap[tx][ty]->map_symbol == 'B' || entitymap[tx][ty]->map_symbol == 'C')) {
                // collect gold
		vector<string> itemReport = p->use(entitymap[tx][ty]);

		if (itemReport[0] == "0") {
			px = tx;
			py = ty;
			p->updatePos(px, py);
			//delete[tx][ty]
			entitymap[tx][ty] = nullptr;
		}
		return itemReport;
        } else if (target == '\\') {
		if (floor == maxFloor) {
			moveReport.push_back("W");
			moveReport.push_back("PC has left the final floor.");
			return moveReport;
		} else {
			p->compass = false;
			newFloor();
			p->clearEffects();
			moveReport.push_back("0");
			moveReport.push_back("");
		}
	} else {
		p->updatePos(px, py);
		moveReport.push_back("0");
		moveReport.push_back("You bumped into something! You cannot move.");
	}
	return moveReport;
}

string Game::attack (int direction) {
	int tx = px;
	int ty = py;

	vector<int> v = getCoordDiff(direction);
	tx += v[0];
	ty += v[1];

	string actionReport = "";
	if (entitymap[tx][ty]) {
		std::vector<std::string> attackReport = p->attack(entitymap[tx][ty]);
		actionReport += attackReport[1];
		if (attackReport[0] == "0") {
			string ereport = entitymap[tx][ty]->report(p);
			char hp = ereport[ereport.find("(") + 1];  // report() on an enemy also gives its hp in brackets. If the first char after a "(" is 0, then that enemy is dead;
			
			if (entitymap[tx][ty]->map_symbol == 'M') {
				p->merchant_hostile = true;
			}
			if (hp == '0') {
				actionReport += "\n";
				unique_ptr<Entity> temp = std::move(entitymap[tx][ty]);
				entitymap[tx][ty] = nullptr;
				actionReport += temp->die(&entitymap, p)[1];
			}
		}
	} else {
		actionReport += "There's nothing to attack.";
	}
	return actionReport;
}

vector<string> Game::use (int direction) {
	int tx = px;
	int ty = py;

	vector<int> v = getCoordDiff(direction);
	tx += v[0];
	ty += v[1];

	string actionReport = "";
	std::vector<std::string> report;
	cout << px << py << endl;
	cout << tx << ty << endl;
	if (entitymap[tx][ty]) {
		std::vector<std::string> itemReport = p->use(entitymap[tx][ty]);
		actionReport += itemReport[1];
		if (itemReport[0] == "0") {
			//delete entitymap[tx][ty];
			entitymap[tx][ty] = nullptr;
		} else if (itemReport[0] == "X") {
			return itemReport;
		}
	} else {
		actionReport += "There's nothing there!";
	}
	report.push_back("0");
	report.push_back(actionReport);
	return report;
}
