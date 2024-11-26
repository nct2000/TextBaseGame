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
	vector<Weapon> weapons = {{"DAGGER",8,50},{"SWORD",22,300},{"BOW",34,800},{"CLAYMORE",42,1500},{"CROSSBOW",56,3000},{"HALBELD",60,5000} };

	//Boss info list
	vector<Boss> bosses = {{"GIANT SLIME",3,"BRONZE",10,3,slimeArt},{"ORC CHIEF",5,"SILVER",18,5,orcArt},{"MINORTAURS",8,"GOLD",30,5,minotaurArt},{"BEHOLDER",10,"PLATINUM",50,6,beholderArt},{"LICH",15,"MYTHRIL",65,7,lichArt},{"THE OVERLORD",20,"ADAMANTITE",80,8,overlordArt}};

	//Rank info list
	vector<Rank> ranks = {{500,"SILVER"},{1200,"GOLD"},{3500,"PLATINUM"},{5000,"MYTHRIL"},{12000,"ADAMANTITE"}};

	//Player start stat
	Player player;

	system("Color 0C");

	//Start intro and input name
	infoStream << gameTitleArt << "\n" << story;
	textBoxClean(infoStream);
	cout << "What is your name ? ";
	getline(cin, player.name);


	// Start the game loop
	mainMenu(player, weapons, bosses, ranks);

	return 0;
}