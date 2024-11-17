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
	bool beaten = false;
	const char* art;

	Boss(string name, int difficulty, string requiredRank, int hp, int weakPoint, const char* art) : name(name), difficulty(difficulty), requiredRank(requiredRank), hp(hp), weakPoint(weakPoint), art(art) {}
};

#endif // BOSS_H