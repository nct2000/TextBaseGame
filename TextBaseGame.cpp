#include <iostream>
#include <string>
#include "Player.h"
#include "Weapon.h"
#include "GameFunctions.h"
#include "constants.h"

using namespace std;

int main() {
	//Weapon info list
	Weapon DAGGER ("DAGGER", 5, 50);
	Weapon SWORD ("SWORD", 10, 300);
	Weapon BOW ("SWORD", 18, 800);
	Weapon CLAYMORE ("CLAYMORE", 25, 1500);
	Weapon CROSSBOW ("CROSSBOW", 32, 3000);
	Weapon HALBELD ("HALBELD", 40, 5000);

	//Player start stat
	Player player;

	system("Color f4");

	//Start intro and input name
	textBox(gameTitle);
	textBox(story);
	cout <<"\nWhat is your name? ";
	cin >> player.name;

	// Start the game loop
	mainMenu(player, DAGGER, SWORD, BOW, CLAYMORE, CROSSBOW, HALBELD);

	return 0;
}