#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
#include "Player.h"
#include "Boss.h"
#include "Weapon.h"
#include "Rank.h"
#include "Ascii.h"

// Function declarations
void textBox(const string& text);
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream);
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons);
void displayShopInfo(Player& player, const vector<Weapon>& weapons);
void checkHealth(Player& player);
void checkRank(Player& player, const vector<Rank>& ranks);
void mainMenu(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks);
void store(Player& player, vector<Weapon>& weapons);
void fight(Player& player, vector<Weapon>& weapons);
void bossfight(Player& player, vector<Boss>& bosses, vector<Rank>& ranks);
void rest(Player& player);

#endif // GAMEFUNCTIONS_H
