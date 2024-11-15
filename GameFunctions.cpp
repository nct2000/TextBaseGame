#include <iostream>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>
#include "GameFunctions.h"
#include "Player.h"
#include "Weapon.h"

#undef max

using namespace std;

//This make a box around the text
void textBox(const string& text) {
	// Split text into lines
	stringstream ss(text);
	string line;
	vector<string> lines;

	while (getline(ss, line)) {
		lines.push_back(line);
	}

	// Get the longest line to determine the box width
	size_t maxLength = 0;
	for (const auto& l : lines) {
		if (l.length() > maxLength) {
			maxLength = l.length();
		}
	}

	// Create a border with enough width to fit the longest line
	string border(maxLength + 4, '*');

	// Print the top border
	cout << "\033[0;34m" << border << "\033[1;31m" << endl;

	// Print each line with padding on both sides
	for (const auto& l : lines) {
		cout << "\033[0;34m*\033[1;31m " << l << string(maxLength - l.length(), ' ') << "\033[0;34m *\033[1;31m" << endl;
	}

	// Print the bottom border
	cout << "\033[0;34m" << border << "\033[1;31m" << endl;
}

//Display equipped weapon
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream) {
	for (const auto& weapon : weapons) {
		if (weapon.equipped) {
			infoStream << "\nWeapon: " << weapon.name << "($" << weapon.cost << ")\n";
			break;
		}
	}
}

//Display player info
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons) {
	//Construct
	stringstream infoStream;
	infoStream << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " dollars. Energy: " << player.energy << "\n";

	//Check if any weapon is equipped and add to the info
	displayWeapons(weapons, infoStream);

	infoStream << "\nAdventure Rank: " << player.rank;
	infoStream << "\n\n1) Go to Store\n2) Rest($50)\n3) Fight";

	// Display the player info inside a box
	textBox(infoStream.str());

	cout << "Action: ";
}

//Display shop info
void displayShopInfo(Player& player, const vector<Weapon>& weapons) {
	//Construct
	stringstream infoStream;
	infoStream << "Welcome to the store! You have " << player.money << " $.\n";
	for (size_t i = 0; i < weapons.size(); ++i) {
		infoStream << i + 1 << ") " << weapons[i].name << " | $" << weapons[i].cost << "\n";
	}
	infoStream << weapons.size() + 1 << ") Back";

	// Display the shop info inside a box
	textBox(infoStream.str());

	cout << "Action: ";
}

//Health check
void checkHealth(Player& player) {
	//Construct
	stringstream infoStream;

	const vector<pair<string*, string>> bodyParts = { {&player.l_a, "Left Arm"}, {&player.r_a, "Right Arm"}, {&player.l_l, "Left Leg"}, {&player.r_l, "Right Leg"} };
	for (const auto& part : bodyParts) {
		if (*(part.first) == "Damaged") {
			infoStream << "Your " << part.second << " is damaged! Rest to heal!\n";
			player.health = "Injured";
			textBox(infoStream.str());
			Sleep(1600);
		}
	}
}

// Promotions based on money(requirement for boss fight)
void checkRank(Player& player) {
	const vector<pair<int, string>> rankPromotions = { {500, "SILVER"}, {1000, "GOLD"}, {3000, "PLATINUM"}, {5000, "MYTHRIL"}, {10000, "ADAMANTITE"} };
	for (const auto& promotion : rankPromotions) {
		int moneyReq = promotion.first;
		const string& newRank = promotion.second;

		if (player.money >= moneyReq && player.rank != newRank) {
			cout << "Promoted to " << newRank << " rank adventurer!\n";
			player.rank = newRank;
			Sleep(1600);
		}
	}
}

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Display menu
void mainMenu(Player& player, vector<Weapon>& weapons) {
	while (true) {
		system("CLS");
		checkHealth(player);
		checkRank(player);
		displayPlayerInfo(player, weapons);

		//ERROR INPUT HANDLE
		int choice;
		if (!(cin >> choice)) {
			clearInput();
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			continue;
		}

		switch (choice) {
		case 1:store(player, weapons); break;
		case 2:rest(player); break;
		case 3:fight(player, weapons); break;
		default:
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			system("CLS");
			break;
		}
	}
}

//Story to buy gear
void store(Player& player, vector<Weapon>& weapons) {
	while (true) {
		system("CLS");
		displayShopInfo(player, weapons);

		//ERROR INPUT HANDLE
		int choice;
		while (!(cin >> choice) || choice < 1 || choice > 7) {
			clearInput();
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			system("CLS");
			displayShopInfo(player, weapons);
		}

		// Function to handle purchasing and equipping weapons
		auto PurchaseAndEquip = [&](int weaponIndex) {
			Weapon& weapon = weapons[weaponIndex];

			if (weapon.purchased) {
				cout << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					clearInput();
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, weapons);
					cout << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					// Equip the selected weapon and unequip all others
					for (auto& w : weapons) {
						w.equipped = &w == &weapon;
					}
				}
			}
			else {
				if (player.money >= weapon.cost) {
					player.money -= weapon.cost;
					weapon.purchased = true;
					cout << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
					int equipChoice;
					while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
						clearInput();
						cout << "Invalid choice. Please enter 1 or 2.\n";
						Sleep(1000);
						system("CLS");
						displayShopInfo(player, weapons);
						cout << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
					}
					if (equipChoice == 1) {
						// Equip the selected weapon and unequip all others
						for (auto& w : weapons) {
							w.equipped = &w == &weapon;
						}
					}
				}
				else {
					cout << "You don't have enough money.\n";
					Sleep(1400);
				}
			}
			};

		// Map the weapon choices to the vector index (assuming weapon list starts at index 0)
		switch (choice) {
		case 1: PurchaseAndEquip(0); break;   // Dagger
		case 2: PurchaseAndEquip(1); break;   // Sword
		case 3: PurchaseAndEquip(2); break;   // Bow
		case 4: PurchaseAndEquip(3); break;   // Claymore
		case 5: PurchaseAndEquip(4); break;   // Crossbow
		case 6: PurchaseAndEquip(5); break;   // Halberd

		case 7:
			return;  // Exit the store
			break;

		default:
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			break;
		}
	}
}

//Fight for money and rank up
void fight(Player& player, vector<Weapon>& weapons) {
	srand(static_cast<unsigned int>(time(0)));
	system("CLS");

	checkHealth(player);

	if (player.energy < 40) { cout << "Not enough energy.\n"; Sleep(1000); return; }

	// Check if the player has any equipped weapon
	bool hasEquippedWeapon = false;
	for (const auto& weapon : weapons) {
		if (weapon.equipped) {
			hasEquippedWeapon = true;
			break;
		}
	}

	if (!hasEquippedWeapon) { cout << "You don't have a weapon equipped.\n"; Sleep(1400); return; }

	int enemiesKilled = 0;
	for (auto& weapon : weapons) {
		if (weapon.equipped) {
			enemiesKilled = rand() % (weapon.damage / 2) + (weapon.damage / 2);
		}
	}
	player.money += enemiesKilled * 15;
	player.energy -= enemiesKilled * 2;
	cout << "Killed " << enemiesKilled << " enemies, earned $" << enemiesKilled * 15 << ".\n";
	if (rand() % 10 < 4) {
		string* limbs[] = { &player.l_a, &player.r_a, &player.l_l, &player.r_l };
		*limbs[rand() % 4] = "Damaged";
	}
	Sleep(1000);
}

//Rest to restore health and energy
void rest(Player& player) {
	system("CLS");
	player.energy = 100;
	player.health = "Full";
	player.money = -50;
	player.l_a = player.r_a = player.l_l = player.r_l = "Normal";
	cout << "You rested and healed.";

	Sleep(1400);
}