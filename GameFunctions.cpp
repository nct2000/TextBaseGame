#include <iostream>
#include <Windows.h>
#include <limits>
#include <ctime>
#include <sstream>
#include <vector>
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
	cout << border << endl;

	// Print each line with padding on both sides
	for (const auto& l : lines) {
		cout << "* " << l << string(maxLength - l.length(), ' ') << " *" << endl;
	}

	// Print the bottom border
	cout << border << endl;
}

//Display player info
void displayPlayerInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld) {
	//Construct the player info string
	stringstream infoStream;
	infoStream << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " dollars. Energy: " << player.energy << "\n";

	//Check if any weapon is equipped and add to the info
	if (dagger.equipped) infoStream << "\nWeapon: DAGGER\n";
	if (sword.equipped) infoStream << "\nWeapon: SWORD\n";
	if (bow.equipped) infoStream << "\nWeapon: BOW\n";
	if (claymore.equipped) infoStream << "\nWeapon: CLAYMORE\n";
	if (crossbow.equipped) infoStream << "\nWeapon: CROSSBOW\n";
	if (halbeld.equipped) infoStream << "\nWeapon: HALBELD\n";

	infoStream << "\nAdventure Rank: " << player.rank;
	infoStream << "\n\n1) Go to Store\n2) Rest\n3) Fight\n\nAction: ";

	// Convert the stringstream to a string
	string playerInfo = infoStream.str();

	// Display the player info inside a box
	textBox(playerInfo);
}

//Display shop info
void displayShopInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld) {
	//Construct the player info string
	stringstream infoStream;
	infoStream << "Welcome to the store! You have " << player.money << " $.\n";
	infoStream << "\n1) DAGGER | $50\n2) SWORD | $300\n3) BOW | $800 \n4) CLAYMORE | $15000 \n5) CROSSBOW | $3000 \n6) HALBELD | $5000 \n7) Back\n\nAction: ";

	// Convert the stringstream to a string
	string shopInfo = infoStream.str();

	// Display the player info inside a box
	textBox(shopInfo);
}

//Display menu
void mainMenu(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld) {
	while (true) {
		system("CLS");
		//Health check
		if (player.l_a == "Damaged") {
			cout << "Your Left Arm is damaged! Rest for a while to fix it!\n\n";
			player.health = "Injured";
			Sleep(1600);
		}
		if (player.r_a == "Damaged") {
			cout << "Your Right Arm is damaged! Rest for a while to fix it!\n\n";
			player.health = "Injured";

			Sleep(1600);
		}
		if (player.l_l == "Damaged") {
			cout << "Your Left Leg is damaged! Rest for a while to fix it!\n\n";
			player.health = "Injured";
			Sleep(1600);
		}
		if (player.r_l == "Damaged") {
			cout << "Your Right Leg is damaged! Rest for a while to fix it!\n\n";
			player.health = "Injured";
			Sleep(1600);
		}

		// Promotions based on money(requirement for boss fight)
		if (player.money >= 500 && player.rank == "BRONZE") {
			cout << "You have been promoted to SILVER rank adventure!\n\n";
			player.rank = "SILVER";
			Sleep(1600);
		}
		if (player.money >= 1000 && player.rank == "SILVER") {
			cout << "You have been promoted to GOLD rank adventure!\n\n";
			player.rank = "GOLD";
			Sleep(1600);
		}
		if (player.money >= 3000 && player.rank == "GOLD") {
			cout << "You have been promoted to PLATINIUM rank adventure!\n\n";
			player.rank = "PLATINIUM";
			Sleep(1600);
		}
		if (player.money >= 5000 && player.rank == "PLATINIUM") {
			cout << "You have been promoted to MYTHRIL rank adventure!\n\n";
			player.rank = "MYTHRIL";
			Sleep(1600);
		}
		if (player.money >= 10000 && player.rank == "MYTHRIL") {
			cout << "You have been promoted to ADAMANTITE rank adventure!\n\n";
			player.rank = "ADAMANTITE";
			Sleep(1600);
		}

		displayPlayerInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);

		//ERROR INPUT HANDLE
		int choice;
		while (true) {
			if (!(cin >> choice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice. Try again.\n";
				Sleep(1000);
				system("CLS");
				displayPlayerInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
			}
			else {
				switch (choice) {
				case 1:
					store(player, dagger, sword, bow, claymore, crossbow, halbeld);
					break;
				case 2:
					rest(player);
					break;
				case 3:
					fight(player, dagger, sword, bow, claymore, crossbow, halbeld);
					break;
				default:
					cout << "Invalid choice. Try again.\n";
					Sleep(1000);
					system("CLS");
					displayPlayerInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					continue;
				}
				break;
			}
		}
	}
}

//Story to buy gear
void store(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld) {
	while (true) {
		system("CLS");
		displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);

		//ERROR INPUT HANDLE
		int choice;
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			system("CLS");
			displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
		}

		//Dagger
		if (choice == 1) {
			if (dagger.purchased) {
				cout << "You already purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = true;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
				continue;
			}
			if (player.money >= dagger.cost) {
				player.money -= dagger.cost;
				dagger.purchased = true;
				cout << "You've purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = true;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//SWORD
		else if (choice == 2) {
			if (sword.purchased) {
				cout << "You already purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					sword.equipped = true;
					dagger.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
				continue;
			}
			if (player.money >= sword.cost) {
				player.money -= sword.cost;
				sword.purchased = true;
				cout << "You've purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					sword.equipped = true;
					dagger.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//BOW
		else if (choice == 3) {
			if (bow.purchased) {
				cout << "You already purchased the BOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the BOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = true;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
				continue;
			}
			if (player.money >= bow.cost) {
				player.money -= bow.cost;
				bow.purchased = true;
				cout << "You've purchased the BOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the BOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = true;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//CLAYMORE
		else if (choice == 4) {
			if (bow.purchased) {
				cout << "You already purchased the CLAYMORE. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the CLAYMORE. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = true;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
				continue;
			}
			if (player.money >= bow.cost) {
				player.money -= bow.cost;
				bow.purchased = true;
				cout << "You've purchased the CLAYMORE. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the CLAYMORE. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = true;
					crossbow.equipped = false;
					halbeld.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//CROSSBOW
		else if (choice == 5) {
			if (bow.purchased) {
				cout << "You already purchased the CROSSBOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the CROSSBOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = true;
					halbeld.equipped = false;
				}
				continue;
			}
			if (player.money >= bow.cost) {
				player.money -= bow.cost;
				bow.purchased = true;
				cout << "You've purchased the CROSSBOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the CROSSBOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = true;
					halbeld.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//HALBELD
		else if (choice == 6) {
			if (bow.purchased) {
				cout << "You already purchased the HALBELD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You already purchased the HALBELD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = true;
				}
				continue;
			}
			if (player.money >= bow.cost) {
				player.money -= bow.cost;
				bow.purchased = true;
				cout << "You've purchased the HALBELD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, dagger, sword, bow, claymore, crossbow, halbeld);
					cout << "You've purchased the HALBELD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = false;
					claymore.equipped = false;
					crossbow.equipped = false;
					halbeld.equipped = true;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}

		//BACK
		else if (choice == 7) {
			break;
		}

		//ERROR INPUT HANDLE
		else {
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
		}
	}
}

//Fight for money and rank up
void fight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow, Weapon& claymore, Weapon& crossbow, Weapon& halbeld) {
	srand(static_cast<unsigned int>(time(0)));
	system("CLS");

	//Health check
	if (player.l_a == "Damaged" || player.r_a == "Damaged" || player.l_l == "Damaged" || player.r_l == "Damaged") {
		cout << "You're injured, rest to heal.";
		Sleep(1400);
		return;
	}

	if (player.energy < 40) {
		cout << "You don't have enough energy to fight.";
		Sleep(1400);
		return;
	}

	if (!dagger.equipped && !sword.equipped && !bow.equipped) {
		cout << "You don't have a weapon equipped.";
		Sleep(1400);
		return;
	}

	//Random earn
	int enemiesKilled = 0;
	if (dagger.equipped) {
		enemiesKilled = rand() % (dagger.damage - 2 + 1) + 2;
	}
	else if (sword.equipped) {
		enemiesKilled = rand() % (sword.damage - 4 + 1) + 4;
	}
	else if (bow.equipped) {
		enemiesKilled = rand() % (bow.damage - 8 + 1) + 8;
	}
	else if (claymore.equipped) {
		enemiesKilled = rand() % (claymore.damage - 12 + 1) + 12;
	}
	else if (crossbow.equipped) {
		enemiesKilled = rand() % (crossbow.damage - 15 + 1) + 15;
	}
	else if (halbeld.equipped) {
		enemiesKilled = rand() % (halbeld.damage - 22 + 1) + 22;
	}
	player.money += enemiesKilled * 15;
	player.energy -= (enemiesKilled * 2);

	// Damage logic
	if (rand() % 10 < 4) {
		int injury = rand() % 4; // Randomly damage a limb
		switch (injury) {
		case 0: player.l_a = "Damaged"; break;
		case 1: player.r_a = "Damaged"; break;
		case 2: player.l_l = "Damaged"; break;
		case 3: player.r_l = "Damaged"; break;
		}
	}

	cout << "You fight, killing " << enemiesKilled << " enemies, making " << enemiesKilled * 15 << " dollars!";
	Sleep(1400);
}

//Boss scene
void bossFight() {
}

//Rest to restore health and energy
void rest(Player& player) {
	system("CLS");
	cout << "You rest, restoring your energy.";
	player.energy = 100;
	player.health = "Full";

	if (player.l_a == "Damaged") {
		cout << "\n\nYour Left Arm was healed.";
		player.l_a = "Normal";
	}
	if (player.r_a == "Damaged") {
		cout << "\n\nYour Right Arm was healed.";
		player.r_a = "Normal";
	}
	if (player.l_l == "Damaged") {
		cout << "\n\nYour Left Leg was healed.";
		player.l_l = "Normal";
	}
	if (player.r_l == "Damaged") {
		cout << "\n\nYour Right Leg was healed.";
		player.r_l = "Normal";
	}

	Sleep(1400);
}