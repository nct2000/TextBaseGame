#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Weapon.h"
#include "GameFunctions.h"
#include "constants.h"

using namespace std;

int main() {
	//Weapon info list
	vector<Weapon> weapons = { {"DAGGER", 6, 50},{"SWORD", 10, 300},{"BOW", 18, 800},{"CLAYMORE", 24, 1500} ,{ "CROSSBOW", 32, 3000 },{"HALBELD", 40, 5000} };

	//Player start stat
	Player player;

	system("Color 0C");

	//Start intro and input name
	textBox(gameTitle);
	textBox(story);
	cout << "\nWhat is your name? ";
	cin >> player.name;

	// Start the game loop
	mainMenu(player, weapons);

	return 0;
}