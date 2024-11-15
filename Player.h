#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player {
public:
	string name;
	string rank = "BRONZE";
	int money, energy;
	string health = "Full";
	string l_a = "Normal"; // Left arm
	string r_a = "Normal"; // Right arm
	string l_l = "Normal"; // Left leg
	string r_l = "Normal"; // Right leg
	int live;

	Player(string name = "Player", int money = 100, int energy = 100, int live = 3) : name(name), money(money), energy(energy) {}
};

#endif // PLAYER_H
