#include <iostream>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <regex>
#include <algorithm>
#include <conio.h>
#include "GameFunctions.h"
#include "Player.h"
#include "Weapon.h"
#include "Rank.h"
#include "Boss.h"
#include "Ascii.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

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

//Clear the error input
void clearInput() {
	cin.clear();
	string discard;
	getline(cin, discard);
}

//Sleep and inore any input when sleep
void sleepAndIgnoreInput(DWORD sleepDuration) {
	DWORD elapsed = 0;
	DWORD interval = 100; //Check input every 100ms

	while (elapsed < sleepDuration) {
		while (_kbhit()) _getch();
		Sleep(interval);
		elapsed += interval;
	}
}

//Function to remove ANSI escape codes from a string
string stripAnsiCodes(const string& str) {
	return regex_replace(str, regex("\033\\[[0-9;]*m"), "");
}

//Function to create a text box around the input text
void textBox(const string& text) {
	stringstream ss(text);
	string line;
	vector<string> lines;

	//Split text into lines
	while (getline(ss, line)) {
		lines.push_back(line);
	}

	//Get the longest visible line to determine box width
	size_t maxLength = 0;
	for (const auto& l : lines) {
		size_t visibleLength = stripAnsiCodes(l).length();
		if (visibleLength > maxLength) {
			maxLength = visibleLength;
		}
	}

	//Create a border with enough width to fit the longest line
	string border(maxLength + 4, '*');

	//Print the top border
	cout << "\033[0;34m" << border << "\033[1;31m\n";

	//Print each line with padding on both sides
	for (const auto& l : lines) {
		size_t visibleLength = stripAnsiCodes(l).length();
		cout << "\033[0;34m*\033[1;31m " << l << string(maxLength - visibleLength, ' ') << " \033[0;34m*\033[1;31m\n";
	}

	//Print the bottom border
	cout << "\033[0;34m" << border << "\033[1;31m\n";
}

//This make a box around the text with empty stream wwhen done
void textBoxClean(stringstream& infoStream) {
	textBox(infoStream.str()); infoStream.str("");
}

//Display equipped weapon
void displayWeapons(const vector<Weapon>& weapons, stringstream& infoStream) {
	for (const auto& weapon : weapons) {
		if (weapon.equipped) {
			infoStream << "\nWeapon: " << weapon.name << " (\033[0;32m" << weapon.damage << " dmg\033[1;31m)\n";
			break;
		}
	}
}

//Display player info
void displayPlayerInfo(Player& player, const vector<Weapon>& weapons, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream) {
	infoStream << "Name: \033[0;32m" << player.name << "  \033[1;31mHealth: \033[0;32m" << player.health << "  \033[1;31mMoney: \033[0;32m" << player.money << " $  \033[1;31mEnergy: \033[0;32m" << player.energy << "  \033[1;31mLives: \033[0;32m" << player.live << "\033[1;31m.\n";
	checkHealth(player, infoStream);
	checkRank(player, bosses, ranks, infoStream);
	displayWeapons(weapons, infoStream);

	infoStream << "\nAdventure Rank: \033[0;33m" << player.rank;
	infoStream << "\n\n\033[32m1) \033[1;31mGo to Store\n\033[32m2) \033[1;31mRest($50 for heal)\n\033[32m3) \033[1;31mFight(more dmg more $)\n\033[32m4) \033[1;31mFight the rank boss(need to rank up)";
}

//Display shop info
void displayShopInfo(Player& player, const vector<Weapon>& weapons, stringstream& infoStream) {
	infoStream << "Welcome to the store! You have \033[32m" << player.money << " $\033[1;31m.\n";
	for (size_t i = 0; i < weapons.size(); ++i) { infoStream << "\033[32m" << i + 1 << ") \033[1;31m" << weapons[i].name << " | \033[32m" << weapons[i].damage << " dmg\033[1;31m| \033[32m$" << weapons[i].cost << "\033[1;31m\n"; }
	infoStream << "\033[32m" << weapons.size() + 1 << ") \033[1;31mBack";
}

//Health check
void checkHealth(Player& player, stringstream& infoStream) {
	const vector<pair<string*, string>> bodyParts = { {&player.l_a, "Left Arm"}, {&player.r_a, "Right Arm"}, {&player.l_l, "Left Leg"}, {&player.r_l, "Right Leg"} };
	for (const auto& part : bodyParts) {
		if (*(part.first) == "Damaged") {
			infoStream << "\nYour " << part.second << " is damaged! Rest to heal!\n";
			player.health = "Injured";
		}
	}
}

//Check rank(requirement for boss fight)
void checkRank(Player& player, const vector<Boss>& bosses, const vector<Rank>& ranks, stringstream& infoStream) {
	int currentRankIndex = -1;
	for (size_t i = 0; i < ranks.size(); ++i) {
		if (ranks[i].name == player.rank) { currentRankIndex = i; break; }
	}

	if (player.rank == "BRONZE") { currentRankIndex = 0; /*Assume BRONZE is at index 0, move to index 1*/ }

	//Check if the player is eligible for the next rank
	int moneyReq = 0;
	string nextRank = "SILVER";
	if (currentRankIndex + 1 < ranks.size()) {
		if (player.rank == "BRONZE") { moneyReq = ranks[currentRankIndex].cost; nextRank = ranks[currentRankIndex].name; }
		else { moneyReq = ranks[currentRankIndex + 1].cost; nextRank = ranks[currentRankIndex + 1].name; }
		for (auto& boss : bosses) {
			//Check if the player's rank matches the boss's required rank
			if (player.money >= moneyReq && boss.requiredRank == player.rank) {
				if (!boss.beaten) { infoStream << "\nYou can fight the \033[0;33m" << boss.name << " \033[1;31mboss to upgrade to \033[0;33m" << nextRank << " \033[1;31mrank adventurer!\n"; break; }
			}
		}
	}
}

//Display menu
void mainMenu(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks) {
	stringstream infoStream;

	//Handle fighting for money logic
	auto handleFight = [&]() {
		if (player.health == "Injured") { infoStream << "You need to recover your health.\n"; }
		else if (player.energy < 20) { infoStream << "Not enough energy.\n"; }
		else if (!any_of(weapons.begin(), weapons.end(), [](const Weapon& w) { return w.equipped; })) { infoStream << "You don't have a weapon equipped.\n"; }
		else { fight(player, weapons); return; }

		textBox(infoStream.str());
		infoStream.str("");
		sleepAndIgnoreInput(1000);
		};

	//Handle boss fight logic
	auto handleBossFight = [&]() {
		int currentRankIndex = -1;
		if (player.rank == "BRONZE") { currentRankIndex = 0; }
		else { for (size_t i = 0; i < ranks.size(); ++i) { if (ranks[i].name == player.rank) { currentRankIndex = i; break; } } }

		int nextRankMoney = (currentRankIndex != -1 && currentRankIndex + 1 < ranks.size()) ? ranks[currentRankIndex + (player.rank == "BRONZE" ? 0 : 1)].cost : 0;

		bool hasEquippedWeapon = any_of(weapons.begin(), weapons.end(), [](const Weapon& w) { return w.equipped; });

		bool canFightBoss = false;
		for (const auto& boss : bosses) {
			if (boss.requiredRank == player.rank && !boss.beaten && player.money >= nextRankMoney && player.health == "Full" && hasEquippedWeapon) { canFightBoss = true; bossfight(player, weapons, bosses, ranks); break; }
		}

		if (!canFightBoss) {
			infoStream << (!hasEquippedWeapon ? "You don't have a weapon equipped.\n" : player.money < nextRankMoney ? "Your money is less than " + to_string(nextRankMoney) + ".\n" : "Your health is not full.\n");
			textBoxClean(infoStream);
			sleepAndIgnoreInput(1000);
		}
		};

	//Main menu loop
	while (true) {
		system("CLS");

		//Live check
		if (player.live <= 0) {
			infoStream << "You DIED!";
			textBoxClean(infoStream);
			infoStream << skeletonArt;
			textBoxClean(infoStream);
			sleepAndIgnoreInput(3000);
			exit(EXIT_FAILURE);
		}

		//Overlord dead check
		if (bosses[5].beaten == true) {
			infoStream << endGame;
			textBoxClean(infoStream);
			infoStream << finalSecret;
			textBoxClean(infoStream);
			infoStream << "The Abyss was no more, the Overlord vanquished, and the artifact now in your possession. The world above awaited you next move—one that would change everything.";
			textBoxClean(infoStream);
			sleepAndIgnoreInput(10000);
			exit(EXIT_FAILURE);
		}

		//Menu here
		displayPlayerInfo(player, weapons, bosses, ranks, infoStream);
		textBoxClean(infoStream); cout << "Action: ";

		int choice;
		if (!(cin >> choice)) {
			clearInput();
			infoStream << "Invalid choice. Try again"; textBoxClean(infoStream);
			sleepAndIgnoreInput(1000);
			continue;
		}

		switch (choice) {
		case 1: store(player, weapons); break;
		case 2: rest(player); break;
		case 3: handleFight(); break;
		case 4: handleBossFight(); break;
		default:
			infoStream << "Invalid choice. Try again"; textBoxClean(infoStream);
			sleepAndIgnoreInput(1000);
			break;
		}
		clearInput();
	}
}

//Store to buy gear
void store(Player& player, vector<Weapon>& weapons) {
	stringstream infoStream;

	//Handle shop info
	auto handleDisplayShop = [&]() {displayShopInfo(player, weapons, infoStream); textBoxClean(infoStream); };

	//Main store loop
	while (true) {
		system("CLS");
		handleDisplayShop();
		cout << "Action: ";

		int choice;
		while (!(cin >> choice) || choice < 1 || choice > 7) {
			clearInput();
			infoStream << "Invalid choice. Try again.\n"; textBoxClean(infoStream);
			sleepAndIgnoreInput(1000);
			system("CLS");
			handleDisplayShop();
			cout << "Action: ";
		}

		if (choice == 7) return;  //Exit the store

		Weapon& weapon = weapons[choice - 1];

		//Handle Equip
		auto handleEquipWeapon = [&]() {
			int equipChoice;
			while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
				clearInput();
				infoStream << "Invalid choice. Please enter 1 or 2.\n"; textBoxClean(infoStream);
				sleepAndIgnoreInput(1000);
				system("CLS");
				handleDisplayShop();
				infoStream << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\033[32m1) \033[1;31mYes\n\033[32m2) \033[1;31mNo"; textBoxClean(infoStream);
				cout << "Action: ";
			}
			for (auto& w : weapons) { w.equipped = (equipChoice == 1 && &w == &weapon); }
			};

		if (weapon.purchased) {
			moveCursorToPosition(0, 10);
			infoStream << "You already purchased the " << weapon.name << ". Would you like to equip it?\n\033[32m1) \033[1;31mYes\n\033[32m2) \033[1;31mNo"; textBoxClean(infoStream);
			cout << "Action: ";
			handleEquipWeapon();
		}
		else {
			if (player.money >= weapon.cost) {
				player.money -= weapon.cost;
				weapon.purchased = true;
				moveCursorToPosition(0, 10);
				infoStream << "You've purchased the " << weapon.name << ". Would you like to equip it?\n\033[32m1) \033[1;31mYes\n\033[32m2) \033[1;31mNo"; textBoxClean(infoStream);
				cout << "Action: ";
				handleEquipWeapon();
			}
			else { infoStream << "You don't have enough money.\n"; textBoxClean(infoStream); infoStream << noMoney; textBoxClean(infoStream); sleepAndIgnoreInput(3000); }
		}
	}
}

//Fight for money
void fight(Player& player, vector<Weapon>& weapons) {
	system("CLS");
	srand(static_cast<unsigned int>(time(0)));
	stringstream infoStream;

	//Calculate kill with weapon
	int enemiesKilled = 0;
	for (auto& weapon : weapons) {
		if (weapon.equipped) {
			enemiesKilled = rand() % (weapon.damage / 2) + (weapon.damage / 2);
			//Chance for treasure drop (10% chance)
			if (rand() % 10 < 1) { int treasureAmount = weapon.damage * 2; player.money += treasureAmount; infoStream << "You found treasure worth \033[32m$" << treasureAmount << " \033[1;31m!\n\n"; }
		}
	}

	//Update player money and energy after the fight
	player.money += enemiesKilled * 15;
	player.energy -= enemiesKilled * 2;

	if (player.energy < 0) { player.energy = 0; }

	infoStream << "You killed \033[32m" << enemiesKilled << " \033[1;31menemies, earned \033[32m$" << enemiesKilled * 15 << " \033[1;31m.\n";

	textBoxClean(infoStream);

	//Random damage to limb
	if (rand() % 100 < 40) { string* limbs[] = { &player.l_a, &player.r_a, &player.l_l, &player.r_l }; *limbs[rand() % 4] = "Damaged"; }
	checkHealth(player, infoStream);
	sleepAndIgnoreInput(1000);
}

//Fight boss for rank up
void bossfight(Player& player, vector<Weapon>& weapons, vector<Boss>& bosses, vector<Rank>& ranks) {
	system("CLS");
	srand(static_cast<unsigned>(time(0)));
	stringstream infoStream;

	//Function to display the time-key text
	auto displayStaticStatus = [&]() {moveCursorToPosition(0, 6); cout << "Time Left:    \033[1;31mseconds | Next Key: ["; };

	//Function to update the time-key text
	auto updateStatus = [&](int timeLeft, const string& nextKey) {
		moveCursorToPosition(11, 6);
		cout << "  ";
		moveCursorToPosition(35, 6);
		cout << "                 ";

		//Write the new dynamic values
		moveCursorToPosition(11, 6);
		cout << "\033[32m" << timeLeft;
		moveCursorToPosition(35, 6);
		cout << "\033[32m" << nextKey << "\033[1;31m] to attack!\n\n";
		};

	//Check if the player's rank matches the boss's required rank
	auto findBoss = find_if(bosses.begin(), bosses.end(), [&player](const Boss& boss) {return boss.requiredRank == player.rank && !boss.beaten; });
	Boss& currentBoss = *findBoss;

	//Only reset combo if the boss's HP is full (indicating a new fight)
	static int bossMaxHP = currentBoss.hp;
	if (currentBoss.hp == bossMaxHP) { player.combo = 0; }

	//Handle to handle rank promotion
	auto handlePromoteRank = [&]() {
		int currentRankIndex = -1;
		for (size_t i = 0; i < ranks.size(); ++i) { if (ranks[i].name == player.rank) { currentRankIndex = i; break; } }

		if (player.rank == "BRONZE") { currentRankIndex = 0; }

		string nextRank = "SILVER";
		if (currentRankIndex + 1 < ranks.size()) {
			nextRank = (player.rank == "BRONZE") ? ranks[currentRankIndex].name : ranks[currentRankIndex + 1].name;
			player.rank = nextRank;
			infoStream << "\nYou promoted to \033[0;33m" << nextRank << " \033[1;31madventurer rank!\n";
			player.live += 3;
			sleepAndIgnoreInput(3000);
		}
		};

	//Handle to handle boss defeat
	auto handleBossDefeat = [&]() {
		moveCursorToPosition(0, 12);
		player.combo = 0;
		currentBoss.hp = 0;
		currentBoss.beaten = true;
		infoStream << "You have defeated the boss!\n";
		handlePromoteRank();
		textBoxClean(infoStream);
		};

	//Boss ASCII art
	moveCursorToPosition(0, 18);
	infoStream << currentBoss.art;
	textBoxClean(infoStream);

	while (currentBoss.hp > 0) {
		int sequenceLength = currentBoss.difficulty;
		vector<ArrowKey> sequence(sequenceLength);

		//Generate a random sequence of arrow keys
		for (int i = 0; i < sequenceLength; ++i) { sequence[i] = getRandomArrow(); }

		//Handle update display info
		auto handleText = [&]() {
			moveCursorToPosition(0, 0);
			infoStream << "Press the following arrow keys in the correct order to deal damage to the boss!!\n";
			infoStream << "BOSS: \033[0;33m" << currentBoss.name << " \033[1;31mHP left: \033[32m" << currentBoss.hp << " \033[1;31mCombo: \033[32m" << player.combo << " \n";
			for (int i = 0; i < sequenceLength; ++i) { infoStream << "\033[32m" << arrowKeyToString(sequence[i]) << "  \033[1;31m"; }
			textBoxClean(infoStream);
			};

		//Display instructions
		handleText();

		//Display static status line
		displayStaticStatus();

		//Start the countdown and game logic
		auto startTime = steady_clock::now();
		int currentIndex = 0;
		bool attSuccess = false;
		int time = currentBoss.difficulty;
		while (steady_clock::now() - startTime < seconds(time)) {
			int timeLeft = time - duration_cast<seconds>(steady_clock::now() - startTime).count();
			string nextKey = currentIndex < sequenceLength ? arrowKeyToString(sequence[currentIndex]) : "None";

			//Update the dynamic parts of the status line
			updateStatus(timeLeft, nextKey);

			if (currentIndex < sequenceLength && isKeyPressed(sequence[currentIndex])) {
				currentIndex++;  //Move to the next key

				//Wait for key release to prevent double detection
				while (isKeyPressed(sequence[currentIndex - 1])) { sleep_for(milliseconds(10)); }
			}

			//Check if the sequence is completed
			if (currentIndex == sequenceLength) { attSuccess = true; break; }

			//Just to prevent high CPU usage
			sleep_for(milliseconds(50));
		}

		///Deal dmg if success or overkill of combo = weakpoint
		if (attSuccess) {
			player.combo += 1;
			if (player.combo >= (currentBoss.weakPoint)) {
				moveCursorToPosition(0, 8);
				infoStream << "Here my Ultimate Skill [\033[0;33mDivine Art\033[1;31m] take that\n";
				textBoxClean(infoStream);
				handleBossDefeat();
				handleText();
			}
			else {
				for (auto const& weapon : weapons) {
					if (weapon.equipped) {
						int dmg = (weapon.damage < 10) ? 1 : weapon.damage / 10;
						currentBoss.hp -= dmg;
						moveCursorToPosition(0, 8);
						infoStream << "You deal \033[32m" << dmg << " \033[1;31mdamage to the boss!";
						textBoxClean(infoStream);
						if (currentBoss.hp <= 0) { handleBossDefeat(); }
						handleText();
					}
				}
			}
			sleepAndIgnoreInput(5000);
			break;
		}
		else { infoStream << "Time's up! You failed to damage the boss in time.\n"; textBoxClean(infoStream); sleepAndIgnoreInput(5000); player.live -= 1; player.combo = 0; break; }
	}
}

//Rest to restore health and energy
void rest(Player& player) {
	stringstream infoStream;

	if (player.money >= 50 && player.health != "Full") { player.energy = 100; player.health = "Full"; player.money -= 50; player.l_a = player.r_a = player.l_l = player.r_l = "Normal"; infoStream << "You rested and healed."; textBox(infoStream.str()); sleepAndIgnoreInput(1000); }
	else if (player.energy != 100) { player.energy = 100; infoStream << "You rested."; textBox(infoStream.str()); sleepAndIgnoreInput(1000); }
	else if (player.health == "Full" && player.energy == 100) { infoStream << "You don't need to rest.\n"; textBoxClean(infoStream); sleepAndIgnoreInput(1000); }
	else { infoStream << "You don't have enough money.\n"; textBoxClean(infoStream); infoStream << noMoney; textBoxClean(infoStream); sleepAndIgnoreInput(3000); }
}