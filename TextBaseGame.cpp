#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <limits>

#undef max

using namespace std;

struct Weapon {
	string name;
	int damage;
	int cost;
	bool purchased;
	bool equipped;
};

struct Player {
	int money;
	int energy;
	string health;
	string name;
	string l_a;
	string r_a;
	string l_l;
	string r_l;
	string rank;
};

// Function declarations
void mainMenu(Player& player, Weapon& m4a1, Weapon& famas);
void store(Player& player, Weapon& m4a1, Weapon& famas);
void fight(Player& player, Weapon& m4a1, Weapon& famas);
void rest(Player& player);

int main() {
	Weapon M4A1 = { "M4A1", 5, 50, false, false };
	Weapon FAMAS = { "FAMAS", 10, 300, false, false };

	Player player;
	player.l_a = "Normal";
	player.r_a = "Normal";
	player.l_l = "Normal";
	player.r_l = "Normal";
	player.health = "Full";
	player.money = 100;
	player.energy = 100;

	cout << "What is your name? ";
	cin >> player.name;
	player.rank = "COPPER";

	// Start the game loop
	mainMenu(player, M4A1, FAMAS);

	return 0;
}

void mainMenu(Player& player, Weapon& m4a1, Weapon& famas) {
	while (true) {
		system("CLS");

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

		// Promotions based on money
		if (player.money >= 500 && player.rank == "COPPER") {
			cout << "You have been promoted to SILVER rank adventure!\n";
			player.rank = "SILVER";
			Sleep(1600);
		}
		if (player.money >= 1000 && player.rank == "SILVER") {
			cout << "You have been promoted to GOLD rank adventure!\n";
			player.rank = "GOLD";
			Sleep(1600);
		}

		// Display player info
		cout << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " dollars. Energy: " << player.energy << "\n";
		if (m4a1.equipped) cout << "Weapon: M4A1\n";
		if (famas.equipped) cout << "Weapon: FAMAS\n";
		cout << "\nRank: " << player.rank;
		cout << "\n\n1) Go to Store\n2) Rest\n3) Fight\n\nAction: ";

		int choice;
		while (true) {
			if (!(cin >> choice)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invalid choice. Try again.\n";
				Sleep(1000);
			}
			else {
				switch (choice) {
				case 1:
					store(player, m4a1, famas);
					break;
				case 2:
					rest(player);
					break;
				case 3:
					fight(player, m4a1, famas);
					break;
				default:
					cout << "Invalid choice. Try again.\n";
					Sleep(1000);
					continue;
				}
				break;
			}
		}
	}
}

void store(Player& player, Weapon& m4a1, Weapon& famas) {
	while (true) {
		system("CLS");
		cout << "Welcome to the store! You have " << player.money << " $.\n";
		cout << "\n1) M4A1 | Assault Rifle | $50\n2) FAMAS | Assault Rifle | $300\n3) Back\n\nAction: ";

		int choice;
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
		}

		if (choice == 1) {
			if (m4a1.purchased) {
				cout << "You already purchased the M4A1. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					m4a1.equipped = true;
					famas.equipped = false;
				}
				continue;
			}
			if (player.money >= m4a1.cost) {
				player.money -= m4a1.cost;
				m4a1.purchased = true;
				cout << "You've purchased the M4A1. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					m4a1.equipped = true;
					famas.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}
		else if (choice == 2) {
			if (famas.purchased) {
				cout << "You already purchased the FAMAS. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					famas.equipped = true;
					m4a1.equipped = false;
				}
				continue;
			}
			if (player.money >= famas.cost) {
				player.money -= famas.cost;
				famas.purchased = true;
				cout << "You've purchased the FAMAS. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					famas.equipped = true;
					m4a1.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}
		else if (choice == 3) {
			break;
		}
		else {
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
		}
	}
}

void fight(Player& player, Weapon& m4a1, Weapon& famas) {
	srand(static_cast<unsigned int>(time(0)));
	system("CLS");

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

	if (!m4a1.equipped && !famas.equipped) {
		cout << "You don't have a weapon equipped.";
		Sleep(1400);
		return;
	}

	int enemiesKilled = 0;
	if (m4a1.equipped) {
		enemiesKilled = rand() % (m4a1.damage - 2 + 1) + 2;
	}
	else if (famas.equipped) {
		enemiesKilled = rand() % (famas.damage - 4 + 1) + 4;
	}

	player.money += enemiesKilled * 15;
	player.energy -= 40;

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