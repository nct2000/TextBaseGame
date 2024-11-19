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
#include "Rank.h"
#include "Boss.h"
#include "Ascii.h"

#undef max

using namespace std;
using namespace chrono;

//Enum for arrow keys for better clarity
enum ArrowKey { UP = VK_UP, DOWN = VK_DOWN, LEFT = VK_LEFT, RIGHT = VK_RIGHT };

//Function to generate a random arrow key
ArrowKey getRandomArrow() {
	int random = rand() % 4;
	switch (random) {
	case 0: return UP;
	case 1: return DOWN;
	case 2: return LEFT;
	case 3: return RIGHT;
	}
	return UP;  //Default case (this should never happen)
}

//Function to display the corresponding arrow key as a string
string arrowKeyToString(ArrowKey key) {
	switch (key) {
	case UP: return "UP";
	case DOWN: return "DOWN";
	case LEFT: return "LEFT";
	case RIGHT: return "RIGHT";
	default: return "UNKNOWN";
	}
}

//Function to check if a specific key is pressed
bool isKeyPressed(ArrowKey key) { return GetAsyncKeyState(key) & 0x8000; }

//Function to position the console cursor
void moveCursorToPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Function to display the static text once on line 3
void displayStaticStatus() {
	moveCursorToPosition(0, 4);
	cout << "Time Left:    seconds | Next Key: [";
}

//Function to update the dynamic parts of the status line on line 3
void updateStatus(int timeLeft, const string& nextKey) {
	moveCursorToPosition(11, 4);
	cout << "  ";
	moveCursorToPosition(35, 4);
	cout << "                 ";

	//Write the new dynamic values
	moveCursorToPosition(11, 4);
	cout << timeLeft;
	moveCursorToPosition(35, 4);
	cout << nextKey << "] to attack!";
}

//Clear the Error input
void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//This make a box around the text
void textBox(const string& text) {
	//Split text into lines
	stringstream ss(text);
	string line;
	vector<string> lines;

	while (getline(ss, line)) {
		lines.push_back(line);
	}

	//Get the longest line to determine the box width
	size_t maxLength = 0;
	for (const auto& l : lines) {
		if (l.length() > maxLength) {
			maxLength = l.length();
		}
	}

	//Create a border with enough width to fit the longest line
	string border(maxLength + 4, '*');

	//Print the top border
	cout << "\033[0;34m" << border << "\033[1;31m\n";

	//Print each line with padding on both sides
	for (const auto& l : lines) {
		cout << "\033[0;34m*\033[1;31m " << l << string(maxLength - l.length(), ' ') << "\033[0;34m *\033[1;31m\n";
	}

	//Print the bottom border
	cout << "\033[0;34m" << border << "\033[1;31m\n";
}

//Display equipped weapon
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream) {
	for (const auto& weapon : weapons) {
		if (weapon.equipped) {
			infoStream << "Weapon: " << weapon.name << " (" << weapon.damage << " dmg)\n\n";
			break;
		}
	}
}

//Display player info
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream) {
	infoStream << "Name: " << player.name << "  Health: " << player.health << "  Money: " << player.money << " $  Energy: " << player.energy << "  Lives: " << player.live << "\n\n";

	checkHealth(player, infoStream);
	checkRank(player, bosses, ranks, infoStream);
	displayWeapons(weapons, infoStream);

	infoStream << "Adventure Rank: " << player.rank;
	infoStream << "\n\n1) Go to Store\n2) Rest($50 for heal)\n3) Fight(more dmg more $)\n4) Fight the rank boss(need to rank up)";
}

//Display shop info
void displayShopInfo(Player& player, const vector<Weapon>& weapons, stringstream& infoStream) {
	infoStream << "Welcome to the store! You have " << player.money << " $.\n";
	for (size_t i = 0; i < weapons.size(); ++i) {
		infoStream << i + 1 << ") " << weapons[i].name << " | $" << weapons[i].cost << "\n";
	}
	infoStream << weapons.size() + 1 << ") Back";

}

//Health check
void checkHealth(Player& player, stringstream& infoStream) {
	const vector<pair<string*, string>> bodyParts = { {&player.l_a, "Left Arm"}, {&player.r_a, "Right Arm"}, {&player.l_l, "Left Leg"}, {&player.r_l, "Right Leg"} };
	for (const auto& part : bodyParts) {
		if (*(part.first) == "Damaged") {
			infoStream << "Your " << part.second << " is damaged! Rest to heal!\n\n";
			player.health = "Injured";
		}
	}
}

//Check rank(requirement for boss fight)
void checkRank(Player& player, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream) {
	int currentRankIndex = -1;
	for (size_t i = 0; i < ranks.size(); ++i) {
		if (ranks[i].name == player.rank) {
			currentRankIndex = i;
			break;
		}
	}

	if (player.rank == "BRONZE") {currentRankIndex = 0; /*Assume BRONZE is at index 0, move to index 1*/}

	//Check if the player is eligible for the next rank
	int moneyReq = 0;
	string nextRank="SILVER";
	if (currentRankIndex + 1 < ranks.size()) {
		if (player.rank == "BRONZE") { moneyReq = ranks[currentRankIndex].cost; nextRank = ranks[currentRankIndex].name; }
		else { moneyReq = ranks[currentRankIndex + 1].cost; nextRank = ranks[currentRankIndex + 1].name; }
		
		for (auto& boss : bosses) {
			//Check if the player's rank matches the boss's required rank
			if (player.money >= moneyReq && boss.requiredRank == player.rank) {
				//Check if the player has already beaten this boss
				if (!boss.beaten) { infoStream << "You can fight the " << boss.name << " boss to upgrade to " << nextRank << " rank adventurer!\n\n"; break; }
			}
		}


	}
}

//Display menu
void mainMenu(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks) {
	//Construct
	stringstream infoStream;

	while (true) {
		system("CLS");
		displayPlayerInfo(player, weapons, bosses, ranks, infoStream);
		textBox(infoStream.str());
		infoStream.str("");
		cout << "Action: ";

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
		case 3: {

			//Check if the player has enough energy
			if (player.energy < 20) { infoStream << "Not enough energy.\n"; textBox(infoStream.str()); infoStream.str(""); Sleep(1000); }

			bool hasEquippedWeapon = false;
			for (const auto& weapon : weapons) { if (weapon.equipped) { hasEquippedWeapon = true; break; } }

			//Check if the player has an equipped weapon
			if (!hasEquippedWeapon) { infoStream << "You don't have a weapon equipped.\n"; textBox(infoStream.str()); infoStream.str(""); Sleep(1400); }
			else if (player.health == "Full" && player.energy >= 20 && hasEquippedWeapon) {
				fight(player, weapons);
			}
		}break;
		case 4: {
			//Find the index of the player's current rank in the ranks vector
			int currentRankIndex = -1;

			//Special case for "BRONZE", which is not in the ranks vector
			if (player.rank == "BRONZE") {
				currentRankIndex = 0;
			}
			else {
				//Find the index of the player's current rank in the ranks vector
				for (size_t i = 0; i < ranks.size(); ++i) {
					if (ranks[i].name == player.rank) {
						currentRankIndex = i;
						break;
					}
				}
			}

			int nextRankMoney = 0;
			if (currentRankIndex != -1 && currentRankIndex + 1 < ranks.size()) {
				if (player.rank == "BRONZE") {
					nextRankMoney = ranks[currentRankIndex].cost;
				}
				else {
					nextRankMoney = ranks[currentRankIndex + 1].cost;
				}
			}

			bool hasEquippedWeapon = false;
			for (const auto& weapon : weapons) { if (weapon.equipped) { hasEquippedWeapon = true; break; } }

			//Loop through the bosses to find the eligible boss for the player's rank
			bool canFightBoss = false;
			for (size_t i = 0; i < bosses.size(); ++i) {
				if (bosses[i].requiredRank == player.rank && !bosses[i].beaten) {
					//Check if the player has enough money and full health
					if (player.money >= nextRankMoney && player.health == "Full"&& hasEquippedWeapon) {
						canFightBoss = true;

						//Logic to initiate the boss fight
						infoStream << "You are ready to fight the boss: " << bosses[i].name << "!\n";
						textBox(infoStream.str());
						infoStream.str("");

						bossfight(player, bosses, ranks,weapons);
						break;
					}
				}
			}

			//Provide feedback if the player can't fight the boss
			if (!canFightBoss) {
				if (player.money < nextRankMoney && player.health != "Full") {
					infoStream << "Your rank is not ready for the boss fight, your money is less than " << nextRankMoney << " and your health is not full.\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(2000);
				}
				else if (!hasEquippedWeapon) {
					infoStream << "You don't have a weapon equipped.\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(2000);
				}
				else if (player.money < nextRankMoney) {
					infoStream << "Your rank is not ready for the boss fight, your money is less than " << nextRankMoney << ".\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(2000);
				}
				else if (player.health != "Full") {
					infoStream << "Your rank is not ready for the boss fight, or your health is not full.\n";
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(2000);
				}
			}
		}; break;
		default:
			infoStream << "Invalid choice. Try again.\n";
			textBox(infoStream.str());
			infoStream.str("");
			Sleep(1000);
			system("CLS");
			break;
		}
		clearInput();
	}
}

//Story to buy gear
void store(Player& player, vector<Weapon>& weapons) {
	//Construct
	stringstream infoStream;

	while (true) {
		system("CLS");
		displayShopInfo(player, weapons, infoStream);
		textBox(infoStream.str());
		infoStream.str("");
		cout << "Action: ";

		//ERROR INPUT HANDLE
		int choice;
		while (!(cin >> choice) || choice < 1 || choice > 7) {
			clearInput();
			infoStream << "Invalid choice. Try again.\n";
			textBox(infoStream.str());
			infoStream.str("");
			Sleep(1000);
			system("CLS");
			displayShopInfo(player, weapons, infoStream);
		}

		//Function to handle purchasing and equipping weapons
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
					Sleep(1400);
					system("CLS");
					displayShopInfo(player, weapons, infoStream);
					infoStream << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
					cout << "\n";
					textBox(infoStream.str());
					infoStream.str("");
					cout << "Action: ";
				}
				if (equipChoice == 1) {
					//Equip the selected weapon and unequip all others
					for (auto& w : weapons) {
						w.equipped = &w == &weapon;
					}
				}
				else {
					//Unequip all weapons when the player chooses not to equip
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
						Sleep(1400);
						system("CLS");
						displayShopInfo(player, weapons, infoStream);
						infoStream << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\n1) Yes\n2) No";
						cout << "\n";
						textBox(infoStream.str());
						infoStream.str("");
						cout << "Action: ";
					}
					if (equipChoice == 1) {
						//Equip the selected weapon and unequip all others
						for (auto& w : weapons) {
							w.equipped = &w == &weapon;
						}
					}
					else {
						//Unequip all weapons when the player chooses not to equip
						for (auto& w : weapons) {
							w.equipped = false;
						}
					}
				}
				else {
					infoStream << "You don't have enough money.\n";
					textBox(infoStream.str());
					infoStream.str("");
					infoStream << noMoney;
					textBox(infoStream.str());
					infoStream.str("");
					Sleep(1400);
				}
			}
			};

		//Map the weapon choices to the vector index (assuming weapon list starts at index 0)
		switch (choice) {
		case 1: PurchaseAndEquip(0); break;   //Dagger
		case 2: PurchaseAndEquip(1); break;   //Sword
		case 3: PurchaseAndEquip(2); break;   //Bow
		case 4: PurchaseAndEquip(3); break;   //Claymore
		case 5: PurchaseAndEquip(4); break;   //Crossbow
		case 6: PurchaseAndEquip(5); break;   //Halberd

		case 7:
			return;  //Exit the store
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

//Fight for money
void fight(Player& player, vector<Weapon>& weapons) {
	system("CLS");
	srand(static_cast<unsigned int>(time(0)));

	//Construct
	stringstream infoStream;

	//Calculate kill with weapon
	int enemiesKilled = 0;
	for (auto& weapon : weapons) {
		if (weapon.equipped) {
			enemiesKilled = rand() % (weapon.damage / 2) + (weapon.damage / 2);
			//Chance for treasure drop (10% chance)
			if (rand() % 10 < 1) { int treasureAmount = weapon.damage * 2; player.money += treasureAmount; infoStream << "You found treasure worth $" << treasureAmount << "!\n\n"; }
		}
	}

	//Update player money and energy after the fight
	player.money += enemiesKilled * 15;
	player.energy -= enemiesKilled * 2;

	if (player.energy < 0) { player.energy = 0; }

	infoStream << "Killed " << enemiesKilled << " enemies, earned $" << enemiesKilled * 15 << ".\n";

	textBox(infoStream.str());
	infoStream.str("");

	//Random damage to limb
	if (rand() % 100 < 40) { string* limbs[] = { &player.l_a, &player.r_a, &player.l_l, &player.r_l }; *limbs[rand() % 4] = "Damaged"; }
	checkHealth(player,infoStream);
	Sleep(1400);
}

//Fight boss for rank up
void bossfight(Player& player, vector<Boss>& bosses, vector<Rank>& ranks, vector<Weapon>& weapons) {
	system("CLS");
	srand(static_cast<unsigned>(time(0)));

	//Check if the player's rank matches the boss's required rank
	auto it = find_if(bosses.begin(), bosses.end(), [&player](const Boss& boss) {return boss.requiredRank == player.rank && !boss.beaten; });

	if (it == bosses.end()) { cout << "\nNo boss available for your current rank (" << player.rank << ").\n"; return; }

	Boss& currentBoss = *it;

	//Only reset combo if the boss's HP is full (indicating a new fight)
	static int bossMaxHP = currentBoss.hp;
	if (currentBoss.hp == bossMaxHP) { player.combo = 0; }

	while (currentBoss.hp > 0) {
		int sequenceLength = currentBoss.difficulty;
		vector<ArrowKey> sequence(sequenceLength);

		//Generate a random sequence of arrow keys
		for (int i = 0; i < sequenceLength; ++i) {
			sequence[i] = getRandomArrow();
		}

		//Display instructions
		cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << " Combo: " << player.combo << " \n\n";
		for (int i = 0; i < sequenceLength; ++i) { cout << arrowKeyToString(sequence[i]) << " "; }

		//Display static status line
		displayStaticStatus();

		moveCursorToPosition(0, 12);
		textBox(currentBoss.art);
		auto startTime = steady_clock::now();
		int currentIndex = 0;
		bool attSuccess = false;

		//Start the countdown and game logic
		int bTime = currentBoss.difficulty + 1;
		while (steady_clock::now() - startTime < seconds(bTime)) {
			int timeLeft = bTime - duration_cast<seconds>(steady_clock::now() - startTime).count();
			string nextKey = currentIndex < sequenceLength ? arrowKeyToString(sequence[currentIndex]) : "None";

			//Update the dynamic parts of the status line
			updateStatus(timeLeft, nextKey);

			if (currentIndex < sequenceLength && isKeyPressed(sequence[currentIndex])) {
				currentIndex++;  //Move to the next key

				//Wait for key release to prevent double detection
				while (isKeyPressed(sequence[currentIndex - 1])) { this_thread::sleep_for(milliseconds(10));}
			}

			//Check if the sequence is completed
			if (currentIndex == sequenceLength) { attSuccess = true; break; }

			//Just to prevent high CPU usage
			this_thread::sleep_for(milliseconds(50));
		}

		moveCursorToPosition(0, 6);

		//Deal dmg if success
		if (player.combo >= currentBoss.weakPoint && attSuccess) {
			player.combo = 0;
			currentBoss.hp = 0;
			currentBoss.beaten = true;
			cout << "Here my Ultimate Skill [Divine Art] take that\n";
			cout << "\nYou have defeated the boss!\n";

			int currentRankIndex = -1;
			for (size_t i = 0; i < ranks.size(); ++i) { if (ranks[i].name == player.rank) { currentRankIndex = i; break; } }

			if (player.rank == "BRONZE") { currentRankIndex = 0; }

			string nextRank = "SILVER";
			if (currentRankIndex + 1 < ranks.size()) {
				if (player.rank == "BRONZE") { nextRank = ranks[currentRankIndex].name; player.rank = nextRank; }
				else { nextRank = ranks[currentRankIndex + 1].name; player.rank = nextRank; }

				cout << "\nYou promoted to " << nextRank << " adventurer rank!\n";
				player.live += 3;
				moveCursorToPosition(0, 0);
				cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << " Combo: " << player.combo << " \n\n";
				Sleep(5000);
				break;
			}

		}
		else if (attSuccess) {
			for (auto& weapon : weapons) {
				if (weapon.equipped) {
					if (weapon.damage < 10) {
						player.combo += 1;
						int dmg = 1;
						currentBoss.hp -= dmg;
						cout << "You deal " << dmg << " damage to the boss!\n";
						moveCursorToPosition(0, 0);
						cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << " Combo: " << player.combo << " \n\n";
						//Check if the boss is defeated
						if (currentBoss.hp <= 0) {
							player.combo = 0;
							currentBoss.hp = 0;
							currentBoss.beaten = true;
							moveCursorToPosition(0, 8);
							cout << "You have defeated the boss!\n";

							//Find and set the new rank
							int currentRankIndex = -1;
							for (size_t i = 0; i < ranks.size(); ++i) { if (ranks[i].name == player.rank) { currentRankIndex = i; break; } }

							if (player.rank == "BRONZE") { currentRankIndex = 0; }

							string nextRank = "SILVER";
							if (currentRankIndex + 1 < ranks.size()) {
								if (player.rank == "BRONZE") { nextRank = ranks[currentRankIndex].name; player.rank = nextRank; }
								else { nextRank = ranks[currentRankIndex + 1].name; player.rank = nextRank; }

								cout << "\nYou promoted to " << nextRank << " adventurer rank!\n";
								player.live += 3;
								moveCursorToPosition(0, 0);
								cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << "\n\n";
								Sleep(3000);
								break;
							}
						}
					}
					else {
						player.combo += 1;
						int dmg = 0;
						int wd = weapon.damage;
						while (wd >= 10) {
							wd -= 10;
							dmg++;
						}
						currentBoss.hp -= dmg;
						cout << "You deal " << dmg << " damage to the boss!\n";
						moveCursorToPosition(0, 0);
						cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << " Combo: " << player.combo << " \n\n";
						//Check if the boss is defeated
						if (currentBoss.hp <= 0) {
							player.combo = 0;
							currentBoss.hp = 0;
							currentBoss.beaten = true;
							moveCursorToPosition(0, 8);
							cout << "You have defeated the boss!\n";

							//Find and set the new rank
							int currentRankIndex = -1;
							for (size_t i = 0; i < ranks.size(); ++i) { if (ranks[i].name == player.rank) { currentRankIndex = i; break; } }

							if (player.rank == "BRONZE") { currentRankIndex = 0; }

							string nextRank = "SILVER";
							if (currentRankIndex + 1 < ranks.size()) {
								if (player.rank == "BRONZE") { nextRank = ranks[currentRankIndex].name; player.rank = nextRank; }
								else { nextRank = ranks[currentRankIndex + 1].name; player.rank = nextRank; }

								cout << "\nYou promoted to " << nextRank << " adventurer rank!\n";
								player.live += 3;
								moveCursorToPosition(0, 0);
								cout << "Press the following arrow keys in the correct order to deal damage to the boss: " << currentBoss.name << " HP left: " << currentBoss.hp << " Combo: " << player.combo << " \n\n";
								Sleep(3000);
								break;
							}
						}
					}
				}
			}
			Sleep(6000);
			break;
		}
		else { cout << "\nTime's up! You failed to damage the boss in time.\n"; Sleep(3000); player.live -= 1; player.combo = 0; break; }
	}
}

//Rest to restore health and energy
void rest(Player& player) {
	//Construct
	stringstream infoStream;

	if (player.money >= 50 && player.health != "Full") { player.energy = 100; player.health = "Full"; player.money -= 50; player.l_a = player.r_a = player.l_l = player.r_l = "Normal"; infoStream << "You rested and healed."; textBox(infoStream.str()); Sleep(1400); }
	else if (player.energy != 100) { player.energy = 100; infoStream << "You rested."; textBox(infoStream.str()); Sleep(1400); }
	else if (player.health == "Full" && player.energy == 100) { infoStream << "You don't need to rest.\n"; textBox(infoStream.str()); Sleep(1400); }
	else { infoStream << "You don't have enough money.\n"; textBox(infoStream.str()); infoStream.str(""); infoStream << noMoney; textBox(infoStream.str()); infoStream.str(""); Sleep(5000); }
}