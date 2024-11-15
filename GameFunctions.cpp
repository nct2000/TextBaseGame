#include <iostream>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "GameFunctions.h"
#include "Player.h"
#include "Weapon.h"
#include "Boss.h"

#undef max

using namespace std;

// Enum for arrow keys for better clarity
enum ArrowKey { UP = VK_UP, DOWN = VK_DOWN, LEFT = VK_LEFT, RIGHT = VK_RIGHT };

// Function to generate a random arrow key
ArrowKey getRandomArrow() {
	int random = rand() % 4;
	switch (random) {
	case 0: return UP;
	case 1: return DOWN;
	case 2: return LEFT;
	case 3: return RIGHT;
	}
	return UP;  // Default case (this should never happen)
}

// Function to display the corresponding arrow key as a string
string arrowKeyToString(ArrowKey key) {
	switch (key) {
	case UP: return "UP";
	case DOWN: return "DOWN";
	case LEFT: return "LEFT";
	case RIGHT: return "RIGHT";
	default: return "UNKNOWN";
	}
}

// Function to check if a specific key is pressed
bool isKeyPressed(ArrowKey key) { return GetAsyncKeyState(key) & 0x8000; }

// Function to display the remaining time
void displayTimer(int timeLeft) {
	//Construct
	stringstream infoStream;
	infoStream << "\rTime Left: " << timeLeft << " seconds remaining to attack...   " << flush;
}

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
			infoStream << "\nWeapon: " << weapon.name << " (" << weapon.damage << " dmg)\n";
			break;
		}
	}
}

//Display player info
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons) {
	//Construct
	stringstream infoStream;
	infoStream << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " $. Energy: " << player.energy << "\n";

	//Check if any weapon is equipped and add to the info
	displayWeapons(weapons, infoStream);

	infoStream << "\nAdventure Rank: " << player.rank;
	infoStream << "\n\n1) Go to Store\n2) Rest($50 for heal)\n3) Fight(more dmg more $)\n4) Fight the rank boss(need to kill to rank up)";

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
	//Construct
	stringstream infoStream;

	const vector<pair<int, string>> rankPromotions = { {500, "SILVER"}, {1000, "GOLD"}, {3000, "PLATINUM"}, {5000, "MYTHRIL"}, {10000, "ADAMANTITE"} };
	for (const auto& promotion : rankPromotions) {
		int moneyReq = promotion.first;
		const string& newRank = promotion.second;

		if (player.money >= moneyReq && player.rank != newRank) {
			infoStream << "Promoted to " << newRank << " rank adventurer!\n";
			player.rank = newRank;
			textBox(infoStream.str());
			Sleep(1600);
		}
	}
}

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Display menu
void mainMenu(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses) {
	//Construct
	stringstream infoStream;

	static string lastBossRank = player.rank;

	while (true) {
		system("CLS");
		checkHealth(player);
		checkRank(player);
		displayPlayerInfo(player, weapons);

		//ERROR INPUT HANDLE
		int choice;
		if (!(cin >> choice)) {
			clearInput();
			infoStream << "Invalid choice. Try again.\n";
			textBox(infoStream.str());
			infoStream.str("");
			Sleep(1000);
			continue;
		}

		switch (choice) {
		case 1:store(player, weapons); break;
		case 2:rest(player); break;
		case 3:fight(player, weapons); break;
		case 4:
			// Check if the player is ready to fight the boss of the current rank
			if (player.rank == lastBossRank && player.rank != "BRONZE" && player.health == "Full") {
				// Find the boss that corresponds to the current rank
				Boss* currentBoss = nullptr;
				for (auto& boss : bosses) {
					if (boss.requiredRank == player.rank) {
						currentBoss = &boss;
						break;
					}
				}

				if (currentBoss != nullptr) {
					// Proceed with the boss fight
					bossfight(player, *currentBoss);
					// After defeating the boss, check if the player should rank up
					checkRank(player);
					lastBossRank = player.rank;  // Update last boss rank fought
				}
				else {
					infoStream << "No boss found for the current rank.\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(1000);
				}
			}
			else {
				infoStream << "Your rank is not ready for the boss fight or your health is not full.\n";
				textBox(infoStream.str());
				infoStream.str("");
				Sleep(1000);
			}
			break;
		default:
			infoStream << "Invalid choice. Try again.\n";
			textBox(infoStream.str());
			infoStream.str("");
			Sleep(1000);
			system("CLS");
			break;
		}
	}
}

//Story to buy gear
void store(Player& player, vector<Weapon>& weapons) {
	//Construct
	stringstream infoStream;

	while (true) {
		system("CLS");
		displayShopInfo(player, weapons);

		//ERROR INPUT HANDLE
		int choice;
		while (!(cin >> choice) || choice < 1 || choice > 7) {
			clearInput();
			infoStream << "Invalid choice. Try again.\n";
			textBox(infoStream.str());
			infoStream.str("");
			Sleep(1000);
			system("CLS");
			displayShopInfo(player, weapons);
		}

		// Function to handle purchasing and equipping weapons
		auto PurchaseAndEquip = [&](int weaponIndex) {
			Weapon& weapon = weapons[weaponIndex];

			if (weapon.purchased) {
				infoStream << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
				textBox(infoStream.str());
				infoStream.str("");
				cout << "Action: ";

				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					clearInput();
					infoStream << "Invalid choice. Please enter 1 or 2.\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(1000);
					system("CLS");
					displayShopInfo(player, weapons);
					infoStream << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
					cout << "\n";
					textBox(infoStream.str());
					infoStream.str("");
					cout << "Action: ";
				}
				if (equipChoice == 1) {
					// Equip the selected weapon and unequip all others
					for (auto& w : weapons) {
						w.equipped = &w == &weapon;
					}
				}
				else {
					// Unequip all weapons when the player chooses not to equip
					for (auto& w : weapons) {
						w.equipped = false;
					}
				}
			}
			else {
				if (player.money >= weapon.cost) {
					player.money -= weapon.cost;
					weapon.purchased = true;
					infoStream << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
					textBox(infoStream.str());
					infoStream.str("");
					cout << "Action: ";

					int equipChoice;
					while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
						clearInput();
						infoStream << "Invalid choice. Please enter 1 or 2.\n";
						textBox(infoStream.str());
						infoStream.str("");
						Sleep(1000);
						system("CLS");
						displayShopInfo(player, weapons);
						infoStream << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
						cout << "\n";
						textBox(infoStream.str());
						infoStream.str("");
						cout << "Action: ";
					}
					if (equipChoice == 1) {
						// Equip the selected weapon and unequip all others
						for (auto& w : weapons) {
							w.equipped = &w == &weapon;
						}
					}
					else {
						// Unequip all weapons when the player chooses not to equip
						for (auto& w : weapons) {
							w.equipped = false;
						}
					}
				}
				else {
					infoStream << "You don't have enough money.\n";
					textBox(infoStream.str());
					infoStream.str("");
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
			infoStream << "Invalid choice. Try again.\n";
			Sleep(1000);
			textBox(infoStream.str());
			infoStream.str("");
			break;
		}
	}
}

//Fight for money and rank up
void fight(Player& player, vector<Weapon>& weapons) {
	srand(static_cast<unsigned int>(time(0)));
	system("CLS");

	//Construct
	stringstream infoStream;

	checkHealth(player);

	//Check if player is injured, they can't fight
	if (player.health == "Injured") { return; }

	//Check if the player has enough energy
	if (player.energy < 40) { infoStream << "Not enough energy.\n"; textBox(infoStream.str());Sleep(1000); return; }

	bool hasEquippedWeapon = false;
	for (const auto& weapon : weapons) { if (weapon.equipped) { hasEquippedWeapon = true;break; } }

	//Check if the player has an equipped weapon
	if (!hasEquippedWeapon) { infoStream << "You don't have a weapon equipped.\n"; textBox(infoStream.str());Sleep(1400); return; }

	//Calculate kill with weapon
	int enemiesKilled = 0;
	for (auto& weapon : weapons) { 
		if (weapon.equipped) { 
			enemiesKilled = rand() % (weapon.damage / 2) + (weapon.damage / 2); 
			// Chance for treasure drop (10% chance)
			if (rand() % 10 <1 ) {
				int treasureAmount = weapon.damage * 2;
				player.money += treasureAmount;
				infoStream << "You found treasure worth $" << treasureAmount << "!\n";
			}
		} 
	}

	//Update player money and energy after the fight
	player.money += enemiesKilled * 15;
	player.energy -= enemiesKilled * 2;

	infoStream << "Killed " << enemiesKilled << " enemies, earned $" << enemiesKilled * 15 << ".\n";

	

	textBox(infoStream.str());

	//Random damage to limb
	if (rand() % 10 < 4) { string* limbs[] = { &player.l_a, &player.r_a, &player.l_l, &player.r_l };*limbs[rand() % 4] = "Damaged"; }
	Sleep(1000);
}

void bossfight(Player& player, Boss& bosses) {
	srand(static_cast<unsigned>(time(0)));

	while (bosses.hp > 0) {
		int sequenceLength = bosses.difficulty;
		vector<ArrowKey> sequence(sequenceLength);

		// Initialize random number generator
		srand(static_cast<unsigned>(time(0)));

		// Generate a random sequence of arrow keys
		for (int i = 0; i < sequenceLength; ++i) {
			sequence[i] = getRandomArrow();
		}

		// Set a 10-second timer
		auto startTime = chrono::steady_clock::now();
		int currentIndex = 0;
		bool attSuccess = false;
		bool keyPressed = false;

		// Display instructions
		cout << "Press the following arrow keys in the correct order to deal dmg to the boss:" << endl;
		for (int i = 0; i < sequenceLength; ++i) {
			cout << arrowKeyToString(sequence[i]) << " ";
		}
		cout << endl;

		// Start the countdown and game logic
		int bTime = bosses.difficulty;
		while (chrono::steady_clock::now() - startTime < chrono::seconds(bTime)) {
			// Get the remaining time
			int timeLeft = bTime - chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
			displayTimer(timeLeft);

			if (currentIndex < sequenceLength) {
				// Check for key press in sequence
				if (!keyPressed) {
					if (isKeyPressed(sequence[currentIndex])) {
						currentIndex++;  // Move to next key in sequence
						keyPressed = true;  // Block further input until the key is released
						system("CLS");
						cout << "Press the following arrow keys in the correct order:" << endl;
						for (int i = 0; i < sequenceLength; ++i) {
							cout << arrowKeyToString(sequence[i]) << " ";
						}
						cout << endl;
						cout << "\nCorrect! NEXT [" << arrowKeyToString(sequence[currentIndex]) << "]" << endl;
						cout << endl;
					}
				}
			}
			else {
				attSuccess = true;
				break;
			}

			// If the player has pressed the correct key, wait for key release before accepting next key press
			if (keyPressed) {
				// Wait for key release before accepting the next key press
				while (isKeyPressed(sequence[currentIndex - 1])) {
					this_thread::sleep_for(chrono::milliseconds(10));  // Just to prevent high CPU usage
				}
				keyPressed = false;  // Reset to allow next press
			}

			// Add a small delay to prevent CPU overuse
			this_thread::sleep_for(chrono::milliseconds(50));
		}

		// End of game feedback
		if (attSuccess == true) {
			bosses.hp -= 1;
			cout << "\nYou damage the boss!" << endl;
			cout << "Boss: "<< bosses.name << "HP: " << bosses.hp << endl;
		}
		else {
			cout << "\nTime's up! You failed to damge the boss in time." << endl;
		}

		// Check if the boss is defeated
		if (bosses.hp <= 0) {
			std::cout << "\nYou have defeated the boss!" << std::endl;
			break;
		}
	}
}

//Rest to restore health and energy
void rest(Player& player) {
	//Construct
	stringstream infoStream;

	system("CLS");
	if (player.money >= 50 && player.health != "Full") { player.energy = 100; player.health = "Full";player.money -= 50;player.l_a = player.r_a = player.l_l = player.r_l = "Normal";infoStream << "You rested and healed.";textBox(infoStream.str());Sleep(1400); }
	else if (player.energy != 100) { player.energy = 100; infoStream << "You rested.";textBox(infoStream.str());Sleep(1400); }
	else if (player.health == "Full" || player.energy == 100) { infoStream << "You don't need to rest.\n";textBox(infoStream.str());Sleep(1400); }
	else { infoStream << "You don't have enough money.\n";textBox(infoStream.str());Sleep(1400); }
}