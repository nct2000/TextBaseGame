#ifndef RANK_H
#define RANK_H

using namespace std;

class Rank {
public:
	string name;
	int cost;

	Rank(int cost, string name) : cost(cost), name(name) {}
};

#endif // RANK_H