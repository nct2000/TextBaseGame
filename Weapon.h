#ifndef WEAPON_H
#define WEAPON_H

using namespace std;

class Weapon {
public:
	string name;
	int damage, cost;
	bool purchased = false, equipped = false;

	Weapon(string name, int damage, int cost) : name(name), damage(damage), cost(cost) {}
};

#endif // WEAPON_H
