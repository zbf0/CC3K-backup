#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <memory>
#include "entity.h"
#include "player.h"

class Game {
	public:
	std::vector<std::vector<std::vector<char>>> maps;
	int floor;
	int width;
	int height;
	int maxFloor;
	// Player location
	int px;
	int py;
	std::unique_ptr<Player> p;
	std::vector<std::vector<char>> floormap;
	std::vector<std::vector<std::unique_ptr<Entity>>> entitymap;
	std::vector<std::vector<char>> rare_entities;

	public:
		Game(std::string race);
		~Game();
		void read_maps(std::string file);
		//std::vector<std::vector<char>>* get_map(int floor);
		void map_load(int floor);
		void map_load();
		// void map_load(std::string file);
		void map_load(std::vector<std::vector<char>>& map);
		void map_generate_test();
		void initRareEntities();
		bool endGame(std::string finalReport);
		void map_print();
		void print_status();
		std::vector<std::string> update();
		// Directions are encoded into keypad notation
		std::vector<std::string> move(int direction);     
		std::string attack(int direction);
		std::vector<std::string> use(int direction);
	private:
		// push a string as a line to floormap
		void newFloor();

};

#endif
