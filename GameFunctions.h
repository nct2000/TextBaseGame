#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Player.h"
#include "Weapon.h"

// Function declarations
void textBox(const string& text);
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream);
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons);
void displayShopInfo(Player& player, const vector<Weapon>& weapons);
void checkHealth(Player& player);
void checkRank(Player& player);
void mainMenu(Player& player, vector<Weapon>& weapons);
void store(Player& player, vector<Weapon>& weapons);
void fight(Player& player, vector<Weapon>& weapons);
void rest(Player& player);

#endif // GAMEFUNCTIONS_H
