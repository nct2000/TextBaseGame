#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Weapon.h"
#include "Boss.h"
#include "GameFunctions.h"
#include "constants.h"

using namespace std;

int main() {
	//Weapon info list
	vector<Weapon> weapons = { {"DAGGER", 6, 50},{"SWORD", 10, 300},{"BOW", 18, 800},{"CLAYMORE", 24, 1500} ,{ "CROSSBOW", 32, 3000 },{"HALBELD", 40, 5000} };

	//Boss info list
	vector<Boss> bosses = { {"GIANT SLIME",3,"SILVER",5,3},{"GOBLIN KING",5,"GOLD",10,5}, {"GOLEM",8,"PLATINUM",15,8}, {"LICH",10,"MYTHRIL",20,12}, {"THE GREAT OVERLOAD",15,"ADAMANTITE",30,15} };

	//Player start stat
	Player player;

	system("Color 0C");

	//Start intro and input name
	textBox(gameTitle);
	textBox(story);
	cout << "\nWhat is your name? ";
	cin >> player.name;

	// Start the game loop
	mainMenu(player, weapons, bosses);

	return 0;
}