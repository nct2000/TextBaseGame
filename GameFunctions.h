#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Player.h"
#include "Weapon.h"

// Function declarations
void mainMenu(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld);
void displayPlayerInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld);
void displayShopInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld);
void store(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld);
void fight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld);
void bossFight();
void rest(Player& player);

#endif // GAMEFUNCTIONS_H
