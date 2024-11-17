#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Player.h"
#include "Weapon.h"
#include "Rank.h"
#include "Boss.h"
#include "GameFunctions.h"
#include "Ascii.h"

using namespace std;

int main() {
	stringstream infoStream;

	//Weapon info list
	vector<Weapon> weapons = {{"DAGGER",6,50},{"SWORD",10,300},{"BOW",18,800},{"CLAYMORE",24,1500},{"CROSSBOW",32,3000},{"HALBELD",40,5000} };

	//Boss info list
	vector<Boss> bosses = {{"GIANT SLIME",3,"BRONZE",5,3,slimeArt},{"ORC CHIEF",5,"SILVER",10,5,orcArt},{"MINORTAURS",8,"GOLD",15,8,minotaurArt},{"BEHOLDER",10,"PLATINUM",20,12,beholderArt},{"LICH",15,"MYTHRIL",30,15,lichArt},{"THE OVERLORD",20,"ADAMANTITE",40,22,overlordArt}};

	//Rank info list
	vector<Rank> ranks = {{500,"SILVER"},{1000,"GOLD"},{3000,"PLATINUM"},{5000,"MYTHRIL"},{12000,"ADAMANTITE"}};

	//Player start stat
	Player player;

	system("Color 0C");

	//Start intro and input name
	infoStream << gameTitleArt << endl << story;
	textBox(infoStream.str());
	infoStream.str("");
	cout << "\nWhat is your name? ";
	cin >> player.name;

	// Start the game loop
	mainMenu(player, weapons, bosses, ranks);

	return 0;
}