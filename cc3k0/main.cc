#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "game.h"

using namespace std;

bool startNewGame(unique_ptr<Game>& game, string file) {
	// Prompt user to choose a race or quit
        cout << "\033[1;36mWelcome to CC3K+!\033[0m" << endl;
        std::string instructions = "Input \033[4mone\033[0m of the following races to begin:\nHuman(\033[35mh\033[0m), Elf(\033[35me\033[0m), Dwarf(\033[35md\033[0m) or Orc(\033[35mo\033[0m)\nEnter q to quit";
        cout << instructions << endl;

        string raceInput;
        while (cin >> raceInput) {
                if (raceInput == "q") {
                        return false;
                } else if (raceInput == "h" || raceInput == "e" || raceInput == "d" || raceInput == "o") {
                        game = std::move(make_unique<Game>(raceInput));
			/*if (file == "") {
				game->map_load();
			} else {
				game->read_maps(file);
				vector<vector<char>>* map_p = game->get_map(1);
				game->map_load(*map_p);
			}*/
			if (file != "") game->read_maps(file);
			game->map_load(1);
			break;
                } else {
                        cout << endl << "\033[1;31mInvalid input.\033[0m" << endl;
                        cout << instructions << endl;
                }
        }
	return true;
}

bool restartGame(unique_ptr<Game>& game, string report, string file) {
	bool continueGame = game->endGame(report);
	if (continueGame) {
		if (!startNewGame(game, file)) {
			return false;
		}
		game->print_status();
		cout << "Player character has spawned." << endl;
		return true;
	} else return false;
}

int main(int argc, char *argv[]) {
	string file = "";
	if (argc > 1) { // When testing, load the file "mappopulatedcoded.txt"
                file = argv[1];
        }

	unique_ptr<Game> game; 
	if (!startNewGame(game, file)) return 0;

	map<string, int> direction; // Using numpad notation
	direction["sw"] = 1;
	direction["so"] = 2;
	direction["se"] = 3;
	direction["we"] = 4;
	direction["ea"] = 6;
	direction["nw"] = 7;
	direction["no"] = 8;
	direction["ne"] = 9;
	direction["n"] = 8;
	direction["e"] = 6;
	direction["s"] = 2;
	direction["w"] = 4;
	direction["1"] = 1;
	direction["2"] = 2;
	direction["3"] = 3;
	direction["4"] = 4;
	direction["6"] = 6;
	direction["7"] = 7;
	direction["8"] = 8;
	direction["9"] = 9;

	map<int, string> cardinals;
        cardinals[1] = "Southwest";
        cardinals[2] = "South";
        cardinals[3] = "Southeast";
        cardinals[4] = "West";
        cardinals[5] = "in no direction";
        cardinals[6] = "East";
        cardinals[7] = "Northwest";
        cardinals[8] = "North";
        cardinals[9] = "Northeast";

	// game->map_load("mappc.txt"); // Here during testing so the command to run is shorter

	game->print_status();
	cout << "Player character has spawned." << endl;
	
	string input;
	while (cin >> input) {
		string actionReport = "";
		string action = input;
		vector<string> moveReport;
		vector<string> itemReport;
		if (input == "u") {
			cin >> input;
			if (direction[input]) {
				itemReport = game->use(direction[input]);
				if (itemReport[0] == "X") {
					if (restartGame(game, itemReport[1], file)) continue;
					else break;
				}
				actionReport += itemReport[1];
			}
		} else if (input ==  "a") {
			cin >> input;
			if (direction[input]) {
				actionReport += game->attack(direction[input]);
			}
		} else if (input == "r") {
			if (!startNewGame(game, file)) break;
			actionReport += "Player character has spawned.";
		} else if (input == "q") {
			break;
		} else {
			if (direction[input]) {
				moveReport = game->move(direction[input]);
				if (moveReport[0] == "W") {
					if (restartGame(game, moveReport[1], file)) continue;
					else break;
				}
				actionReport += moveReport[1] != "" ? moveReport[1] : "PC moves " + cardinals[direction[input]];
			}
		}
		vector<string> updateReport = game->update();
		string tickReport = "";
		string observeReport = "";
		string statusReport = "";

		if (updateReport.size() > 1) {
			tickReport = updateReport[0];
			observeReport = updateReport[1];
		} else {
			statusReport = updateReport[0];
			if (restartGame(game, actionReport + statusReport, file)) continue;
			else break;
		}

		if (direction[action]) {
			if (observeReport != "") {
				if (moveReport[1] == "") actionReport += " and sees " + observeReport;
				/*else {
					cout << actionReport << endl;
					cout << "You see " + observeReport << endl;
					continue;
				}*/
			} else if (moveReport[1] == "") actionReport += ".";
		}
		cout << actionReport << endl;
		if (tickReport != "") cout << tickReport.substr(1) << endl;
	}
}
