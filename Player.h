#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {
public:
    string name;
    string rank;
    int money;
    int energy;
    string health;
    string l_a; // Left arm
    string r_a; // Right arm
    string l_l; // Left leg
    string r_l; // Right leg

    // Constructor
    Player(string name = "Player", int money = 100, int energy = 100) : name(name), money(money), energy(energy), health("Full"), l_a("Normal"), r_a("Normal"), l_l("Normal"), r_l("Normal"), rank("BRONZE") {}
};

#endif // PLAYER_H
