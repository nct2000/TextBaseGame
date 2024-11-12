#ifndef WEAPON_H
#define WEAPON_H

#include <string>

using namespace std;

class Weapon {
public:
    string name;
    int damage;
    int cost;
    bool purchased;
    bool equipped;

    // Constructor
    Weapon(string name, int damage, int cost) : name(name), damage(damage), cost(cost) { purchased = false; equipped = false; }
};

#endif // WEAPON_H

