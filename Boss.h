#ifndef BOSS_H
#define BOSS_H

using namespace std;

class Boss {
public:
	string name;
	int difficulty;
	string requiredRank;
	int hp;
	int weakPoint;

	Boss(string name, int difficulty, string requiredRank, int hp, int weakPoint) : name(name), difficulty(difficulty), requiredRank(requiredRank), hp(hp), weakPoint(weakPoint) {}
};

#endif // BOSS_H