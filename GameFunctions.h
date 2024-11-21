#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
#include "Player.h"
#include "Boss.h"
#include "Weapon.h"
#include "Rank.h"
#include "Ascii.h"

// Function declarations
void textBox(const string& text);
void textBoxClean(stringstream& infoStream);
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream);
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream);
void displayShopInfo(Player& player, const vector<Weapon>& weapons, stringstream& infoStream);
void checkHealth(Player& player, stringstream& infoStream);
void checkRank(Player& player, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream);
void mainMenu(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks);
void store(Player& player, vector<Weapon>& weapons);
void fight(Player& player, vector<Weapon>& weapons);
void bossfight(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks);
void rest(Player& player);

#endif // GAMEFUNCTIONS_H
