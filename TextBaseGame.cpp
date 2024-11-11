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

const char* gameTitle = R"(
		:;;;::::::::;;;::::::::::::::::::::::;::;;:::::::::;;;;;;;;;;;;;::::::::::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::::::;;;;;;;;;;;;;;;:::::::::::::::::::::::::::::::;;;++++++++++++++++;;;++++x++;;::
		::::::::::::::::;:::::::::::::::::..:::::::::::::::::::::::;;::;;;;;:::::::::;;:;:::;;;;;;;;;;;;:::::::::::::::::::::::::;:;;;;;;;;;;;++++;:::::;;;;++++++::::::::::::;+++;;;++;;;;;;:;;;;::;++;;;;;;;;::
		;;::::::::;::::::::::::::::::::::::::::::::::::;::::::::::::::;;;;;;;;::::::::::::::::::::::::::::::::::;;;;;;;::::::::::::::::;;;;;;xX$$X;;:::;;;;;;;;;;::::::::::::;+++++++;;;;;;;::;;::::;;;;;;;;;;;;:
		;;;;;;;;;::;::::::::::::;;::::::::;::::::::...:::::::::::::::::::::;;;;;;;::::::::::...::::::::::::::::::::;;:::::::::::::::::::::::::+x+:::::::::;;;;;;::::::::::::++++++++;;;;;;;;;;;::::;;;;;;;;;;::::
		;;;;;;;;;:::::::::::::::::::::::::::::;;;::::::::::::::::::::::::::::::::;;:::::::::::......:::.....:::::::::::::::::::::::::::::::::;;;:::::;;;;;;;;;;:::::::::::;+++++++;;;;;;;;;:::::::;;;;;::::::::;;
		::::::::::::::::::::::::::::::::::;;:::::::::::::::::::;;;;;:;::::::::::::::::::::::::.............:.....:::::::::::::::::::::::::.:::;;;;;;;;;;;;;;+;:::::::::::++++++;;;;;;;::::::::::::::::;:;;;;:::;;
		;;;::::::::::::::::::::::;:::::::::::::::::.::::::..:::;;;;;;;;;;;;;;;;;:::::;;;::::::....:::.....::..:.:::::::....:....:::;;;;;;;::::::;;;;;::::;;;::::::::::;;;;+;;;;;::;;:::::::::::::::::::::;;+++;::
		::::;::::::::::::::::::::::::::::::::::::::::::::::::::::::;;;;;;;;;;;::::::::::;;::::::::::::+XX$$$XXx;:::::::::::::::::::::;;;;;;;::::::;;;;;;:::::::::::::::::;;;::;;;;;::::::::::::::::::::;;+++:::::
		:::::::;:::::::::::::::::::::::::::::::::::::::::::::::::;::::;;;;;;;;;;;;::::::::::::::::::x$$XxxxxxxX$x:;;::::::::::::;;;;;;;;;;;;;:::::::;;;::::::.:::::::::::;;;;;;;;;;:::;;;;:::::::::::;;;;::::::::
		;;;;;;;;:::::::::::::::::::..:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::x$$X+++;;;;;+xXX;+++;;;;+++++;;:;;;;;;;;::::::::...:::::::::;;;;;;;;;;;;++++++;:::::;;;::::::::::;;;;:::::.::;+
		;;;;;;;;;;;::::::::::::::::::::::::::::::::::::::.:::::::::;;;::::::..::::::::::::::::;;;X$$Xx;;;;:::;;++XX++++;;;++++++++++++++++++;;;::::;+;:::::::;;;;++++++++++++;;;::::::;;;;:;:::::::;:::::.:::;;;+
		;;;;;;;;:::::::::::::::::::::::::::.::::::::::::::...::::::::::::::::::::::::::::::;+xxxX$XXxxxXXx+xXXXXXX$Xxxx+;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::;;;;;;+++;;:::;;:::::::;+;;::::::::::::::::;;;::
		;;;;;:::::;::::::::::::::::::::::::::::::::::::::..::...:...:::::::::::::::;;++;;++++XX$$$X$X...;x++x;..:XX$$xxx:::::::;;;;;;;;;;;;;;;;;::::::::::;;;;;:::;;;;;;;;;;;:::::::::::::....::::::::::::::::::;
		;:;;;:::::;;;;::::::::;::::::::::::::::;:::::::::::::::::::.......::;+++++++++++++++XXX$$$$$:;;::....:;;;Xx$$$xxx::::::::::;:::::::;;;;;;;;::::::::;;;;;;:;;;;;;;;;;::::::::::::::...::::;x:...::::::::::
		;;:::;;:::::;;;:::::::;;::::::;;;:::;xxx;::::::::::::::::::::.:+xx+;;;+++++++++;;;:+XX$&$$x+:::;;$xx$;;::;Xx$$$XX+:::::::::::::;;;;;;+++;;::::::::::;;;;::.::::;;:::::::::::::::::::::;xx;.::::::::::::::
		;;;:::::::::::::::::::;:::::::;;;:::;+;:::::::::::::::::::::::::::::::::::::....:.;XX$$$$Xx++xxxx$$$Xx;x+xxX$$$$$$;:::::::::::::::::;++;;::::;;;::::;;;;;;;::::;;:::::::::::::::::::+xxx:::::::::::::::::
		;;;;::::::::+;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::..:XX$$&$&$Xxxx$$Xxx+xX$XxxxX$$$$$$$;::::::::::::::::::::::::;;;;:::::::;::::::::::::::::::::::::::+xxx+::::::::::::::::::
		;;;;::::::::::::::::::::::::::::::::::::::::::::::::::::::..:::::::::::::::::::::xX$$$&$&$XXx$$$$$$$$&$$$xX$$$$$$$$$+:::::::::::::........::::::::::::::::::..:::::::::::::::::;+++++::::::::::::::::::::
		;;;;;;;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::.::::::::::::::xX$$$$&&&$$$$&$X$XxxX$$$$$$$$$$$$$$$$+.:....:::::::::::::::::::::::::::::::::::::::::::::::::;;++;;::::::::::::::::::::::
		;;;;;;:::;;:::::::::::::::::::::::::::::::::::::::.::::..:::::::::::::..:::::::x$$$$$$&&&&$$&$X+;+xx;:+X$$$&&&$$$$$$$$;...:::::;;::::::::::::::::::;:::::::::::::.:..::..::;;;;;;;::::::::::::::::::::;;:
		::::::::::::::::::...::::::::::::::::::::::::::::::;:::.:::::::::::::::::.....+$$$$$$$$&&&&&&$$Xx+;;+XX$$$&&&&$$$$$$$$$:::::::::::::::::..:::::::x$+:::::::............;++;;;;;;::::::::::::::::::::::;;;
		...............:..:...::.:::::::::::::::...:::::::::;::::::::::::;;::::::::...+$$$$$$$$&&&&&&&$$XX$$XX$$&&&&&&$$$$$$$$Xx:::::::::...:::...::::::;;;:::::::::::::::...;++++;::;;..:::...............::::::
		.......::::................:::::::::::::.....:::::::::.::::::::::::::::::::::.:X$$$$$X$$&&&&&&&$$$XXXXX$&&$&&&$$$X$$$XX;.:::::::::::::::::...:........:::::::::.:;;;;;;++;:::............::::............
		...........::..............................::::+xx+++::::::::::::::::::::::::..:XXXXX$XX$&&$$$$$$XXXX$$$$$$$$$&$$$XXXXx.:::::::::::::::::::....:::::::::::::::;++x+;::::........:::................::::..
		.................................::::..:::....:+++++x:::::::::::::::::::::::.....xXXXX$$$$$$$$X$XX$$$$XXX$$$$$$XXXx;++....::::::::............::::....:::::+++xx++;:....::::....:....................::::
		..::...:::..............................:.....:++++++:::.:::::::::::::::::.:...;xXXxxXXXXX$&&$x+xXxxXxXX$$$$XXXXX+:x$$:......::::::::..:::::::::::::::.;++xxx++;.:..::....:..............::...::..:::..::
		::..........................:..............::::+++++::.:::::::::::::::.:;;;;;+xxXX$$++xxxXXX$&$$$xXXX$$$$$$XXXX+:x$$$X+;;:::::::.::::::.....::::.:.:;+xxxx++:...::....................:.........::..:::..
		:..:........................::..:...........:::+xxxx;;:::::::::::::.:xxxxx+;:::;+xX$$X;;+xxxX$$$$+$$XX$$$XXx;;xX$$$XX++;:;::;;+++;:::::::::::::::;+xxxxxx+.:..................................:.....::..:
		::........::::::::::::......::....:.........:::;+xxxx+;:::::::::::;xXXXXxxxxxx+;::;+x$$X;:;++XX$$xxxx$$$x;;x$$$$$XXx+;;+++xxXXXXXXXx:::::::::;xxXXXXxxx+.:..................::::::::::::......::.:.::.:::
		..........:::::::::::::::...:..:..............:::++xxxx+:::::::;xXXXXxx+++xxx++;:;;:::+xxXXx;;;x$X$XX$X+X$$$XXx+:::;+++xxx+;;;+++xXXXXX..:;XXXXXXXxxx+....................:::::::::::;::........:.:::.::.
		............::...::::::::::........:......:...:::.+xxxXXxx:::;+xXXXXXXxxXXx++;......+++xX$$$$$X++$$$XxXXX$$$Xx+;:...:::;;xxxXXXXXxxxxxXX$$$$XXXXXx+:........:.............:::::::::::::.....:.......::..:
		.................::::::..::......:.::.:::..:.:....::xXXXXXXx++XXXXXXXXXXx;:;+xXX$XX+:..:::Xx+xxxXX+xxxxxxxx;.:..:x$$$$X;;::::::xXX$$$$$$$$$$Xxx;::::.......:.::........::::::::.:::...............:...:;;
		..:::.::.:...:::................::.::.:.::.:.:.:::::::xxXXXXXxxXX$XXx;::;xx+;..XXXX+;;.:;::::::;:::::::::::.;;.;;:X$$$$$$$$$$$$$$$$$$$$$$Xx;:::::::.:.:.::::..:.::.....................:::.:::.::...:;;;;
		::..:::::.:..:::.......::.........::.:::::.:.:.::::::::xxXXXXXXxXx:::;;;;;;..$$$XXxx;++;xx+++;::.+;+.:::;+;+x;+++xxXX$$$$$$$$$$$$$$$$XX+;+x;;::::::.:.:.:::::.:::.:...........:::..::..:::..:.::::..::;;+
		::;;;;:;::...::::.....:::....:.....::::.:::....::::::::::xXXX$$$Xx+;;;:;:.;$&$$XX+.:++Xx++:::::::;;;:;:::::+++Xx+:.;x+X$$$$$$++XXxXX++XXXXx+;;;:::;:.:.::::.:::......:....:::::::..::.::::...:;;..:;:::;;
		;;;;;+;:+;;:..:+++:...;+;..::.:::..:::.::..:.:::::::::::;+xXxX$$$$$$XxX$$$$$$$XX;::+;x::::+::::;:X;X::;;::;;:::x++:::xX$$$$$XxXx+++x$$;:Xxxxxx;::::::....::.:::..:::.::::::::::++:...;++;..:;++.:;;;;+;;+
		;;;;;;++;;+++;;;xx+;:;++;....:............:::::::;:::::;;+XXx;;X$$$$$$$$$$$$$$X++++++++x;::;;;;;:xXX::;;;;:::x+++++++xXX$X$$X++xXXx+xX$X::;:;+;+x;::::::..::....:..::::::::...:++;::+xx+;;+x+;;;;;;;;++++
		;;;;;;;+xxxx+++++xxxx++++;:.......::::::::::::::::::::::;;::;;;+x$$$$$$$$$$$$XX++++++;;::.;:;;;;+xXX;;+;;:;::+++++xx++XXXx$$$$$XxX$$X+;;;:::xxx:::;;;+;;:::::::::......::...::+++++xxxxxxxxxxx+::;;;;;;++
		:;;;;;;;;;;;+xxxx+xxxxxxx++++;.::::::::::::::::::::::::::;xx;++++xX$$$$$$$$$$xxxx+++++++++x++++x+xXXx+++++x;+++x++++++X+;x+$$$$$$$X;;;::::;:..:;+xxx++;;;;+++;;;:::::::..:++++++xxxxxxxxxxx:::::::;;;++++
		::::;;;;;;;;;;;xxxxxxxxxxxxxxx+x:.::::::::::::::::::::..;++;:+;+xx++X$$$$$$XXx+xxxx+xxx++x+++++++XXXx+++++xxx++xxxx+++:;+;xX$$$$$XX;;::;:::::;+X:..:;+x+++++++++++++:.:;+xxxxxxxxxxxxxxx+::::::;;;;++xxxx
		;:::::::::::::;;;;+xxxxxxxXXXXX+:::;::::::::::::.::.:+;xXXXx+;;;;xxx+xxXXxxxxx+x+xxxxxxxxxxx+;;xxX$Xxx+;+xxxxxxxxxxx;:;;+++xxxxxxx+;;:::::;++xx$$$$$$$:::+xxxxxx+;+;x;:;xXXXXXxxxxxxx;;+++++++;;;++++++++
		;:::::::::::::::::::::xXXX$$$XXXx+xx+;;:::::::::::;:+XXXxXxXx::::;+xxx;++;;++x++++:+x+++xXxxxxxxxXXXxxxx+xxxX::;++::::::::::::::;;;;;;;;::::;;;;;x$$$$$$$$$+:;x:;+;+xXxxXXXXXXXXx+::::;;;;;;;;;;;++++++xx
		::::::::::::::::::::::::+XXXXXXXX$XXX:++;::::::.+;;;;+xXXXX;:+;::;:;;;++;;;;::;;+++++;+xxx++xxx++xXxx+xxxx+xx++::::::..........:;;++;:::;::;+;;+XXX$$$$$$$$+.++xx;xXX$$$$$$$$$Xx++++++;;;;++++++++;;;+xxx
		::::::::::::::::::::::::::+xXX$$$$$$$x+:+:;;::::;;;+x+++;;;:+xx+;::::::....::::::;;;+++++++;+;;++xXx++++x;+++;;:::.............::;;:::;;;:::::+xx;;+x$$$$x;.XX;+x;$$$$$$$$X$$xxxxxxx++++++++++;;++++++xxx
		:::::::::::.::::::::;;::::;$$$$$$$$$$$X+xxX;++;:.::::::.::::;;++;;;;;::..........:::;;;;:;;::;:::;++;:::::;::::...............:::::;;++;;;;;x;+xXX$+;;++x+;XXXxxX$$$$$$$$$$$xxxxxx++;;;++X$X;;+++++++++++
		:;:::::;;::::::::::::::::::$$$$$$$$&&$XXXX$Xx+:::;::::::::;;:::::;....................:::::::::::;;;::::::::.......:..........:::::;;;++;;;x+XX$$+;+x+xxX:::$$X$$$$$$$$$$$$$$$$$$$$$$$$$$X;;;++++++++++++
		++++++++++;;;;;;;;;;;;;;;;;;x$$&&&&&&Xxx$$$xxX::;;;:;+;::+;:;+::::::....::::::............:::.::::::..::.:.:.....................:::;;++;;;xX+xX+++xxXXXX.xx$$XX$$&&&$&&&$$$$$$$XXXXXXXXX;;;;++++++++++++
		++++++++++++++;;:;;;;;;;;;;;;;;&&&&&&$x+$&&$++$x:$x;:;+x;::+x+;:..........::::::::::............:::::...::.................:::.....:;;;;;+XX+XXxxxXXXXXXXx+&$$$$$$$$&&&$$$$$XXXXXXXXXXXX;;;;;;;;;;;;+++++
		++;;;+++++++++++;;;;;;;;;;;:::::+X$$$$&&&&&$x++$$x$$x:;+x+;::+:.................................:::::..................................;;xxxxXxxxXX$$$$$$$X$&&$$$$$&$$XXX$$XXXXXXXXxx+;::::::;;;;;;;+++++
		xx++;;;+++++++++++++;;;;;;;;;::::::&&&&&&&&$$$&$$$X$$;;;+x+;::.........................................................................;;+xxXXxXXX$$$$$$$$$X$&&&&&&$XXXXXXXXXxxxxx:::::::::;;;++;;;;++++;
		xxx+++++;++++++++++++++;;;;;;;;:::+$$$&&$$&$$$$$$$X$$$:;;+++::..................................;;;;+;..............................::::+xxXX$$$$$$$$$$$$$$XX$&&&&$$XXXXXXXxxxx;::::::::::::;;+++;;;+++++
		+++;:;+++++++++++++++++++++;;;;;::X$$$$&&$$&&$$$$$$$$$+:;;+xxx++++++Xxxx:;;Xxxxxxx+xxx+++;::.:+++xXXXXx;..::;++xxxxxxXxxxXx;;xxxxxxxx+x+++XxX$$$$$$$$$$$$$$$XX$&&&&&$$XXXXxxx::::::..:::::;;;;::;;;;;++++
		+++;;;+++++++++x++xx++++++++;;;;::X$&$$$&&&&$$&$$$$$$$$:+;:x$$$X$X$$$$$$XXX$$$$$$$$$$$$$$$$$$XxXX$$$$$$X$$$$$$$$$$$$$$$$$$$XX$$$$$$$X$$$$$xXX$$$$$$$$$$$$$$$$$XX&&&&&$$XXXxxx:::::::::::::::::::::;;++++x
		+xxx++++++;;;++++++++;;;;;;;;;::::X$$$$$&&&&&&&&&&&$$$$::;;:X$$$$$$$$$$$$XX$$$$$$$$$$$$$$$$$$$$$XXXXxX$$$$$$$$$$$$$$$$$$$$XX$$$$$$$$$$$$$xxXX$$$$$$$$$$$$$$$$$$xX&&&&$$$XXxx:::::::::::::::::::;;:;;+;;;+
		+++++++;;;;;;;;;;;;;;;;;::::::::::X$$$$$&&&&&&&&&&&&&$$X:;;::$$$$$$$$$$$$$XX$$$$$$$$$$$$$$$$$$&&$$$$&&&&$$$$$$$$$$$$$$$$$$X$$$$$$$$$$$$$x++X$$$$$$$$$$$$$$$$$$$$Xx&&&&&$$Xx:::::::::::::;;;;;;::::;;;;;++
		+;;;;;;:::::::::::;;;:::.::::::::xX$&$$$$$$&&&&&&&&$$$$$::;;::$$&X$$$$$$$$XX$$$$$$$$$$$$&&$$$$&&$$$$$&&&$&$$&$$$$$$$$$$$$XX$$$$$$$$$X&$;+xxX$$$$&$$$$$$$$$$$$$$$$$x&&&&&$$$X::::;;+;;;;;;;+++;;+xxxxxxxXX
		;;:::::;::::::;;;;;;;:;::::::::::XX$$$$$$&$$&&&&&&&$$$$$X:;;;::X$$$$$$$$$$$XX$$$$$$$$$$&$$$$&&$$$$$$&&$$$$$$$$$$$$$$$$$$XX$$$$$$$$$$XX++xXXXX$$$$$$$$&$$&$$$$$$$$$$x$&&&&$$$$$Xx++++;;;++;;xxxxxxxXXXXXXX
		+++;::::::::::;::+++;::::::::::::XXX$$$$$$$$&$$&&&&$$$$$$x:;;;:;$$$$$$$$$$$$X$$$$$$$$$$&$$$$$&&&&$$$&&&&$$$$&$$$$$$$$$$$XX$$$$$$$$$$$x++xXXXXXX$&&&&&&&&&$$$$$$$$$$$XX&&&&$$&$$$$$$$$$X++xxxxXXX$X$$$$$XX
		XXx;:::::::::::::::::::;;;+++;;;:xXX$$$$XX$&&$$&&&&&&$$$$$;+++;;$$&&&&$$$$$$XX$$$$$$$$$$$$$$$$&&&$$$&&&$&$$$$$$$$XxX$$$$X$$$$$$$$$$$$$xxxXXXXXXXX$&&&&&&&$$&&$$$$$$$$$XX$&&&&&$&&&$$x+xxxxX$$$$$$$$$$$$$$
		x+;::::::;;;:::::;+++x+++++++;;;::XXX$$$$XX$&$$&&&&&&&$$$$X+xx+++$&$&&&$$$$$$X$$$$$$$$$$$$$$$$$&$$$$$$$$$$$$$$$$$$$$$$$X$$$$$$$$$$$$$$$xxXXXXXXXXXX$$$$$$$$&&$$$$$$$$$$$$X$&&&&&$XxxXXXX$$$$$$$$XXXx++++x
		x+++;;;::;;:::+++xxxxx+++++++;;;;:xXXX$$$XXX$$$$&&&&&&$$$$$xxxx+++$&&$$$$;$$$XX$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$X$$$$$$$$&$$$$$&$xXXXXXXXXXXXX$$$$$$$$$$$$$$$$$$$$$&&$$$$$$$$$$$$XXXxxxxxx+;;;;;+X
		;;;++;;;:::::++++++++++++++++;;;:::xXXX$$$XXXX$$$&&&&$$$$$$$+xxx+++X$$$$$$$$$$X$$$$$$$$$$$$$$$$$$$$$$&$$&$$$$$$$$$$$$$$X$$$$$$$$$X;++X&x&+XXXXXXXXXXXXXX$$$$$$$$$$$$$$$$$$$$$$$$$$$$XXXXXXXXXXXx++;;;+xXX



    :::       ::: :::::::::: :::        :::           ::::::::   ::::::::    :::   :::   ::::::::::      ::::::::::: ::::::::      ::::::::::: :::    ::: ::::::::::              :::     :::::::::  :::   :::  ::::::::   :::::::: 
   :+:       :+: :+:        :+:        :+:          :+:    :+: :+:    :+:  :+:+: :+:+:  :+:                 :+:    :+:    :+:         :+:     :+:    :+: :+:                   :+: :+:   :+:    :+: :+:   :+: :+:    :+: :+:    :+: 
  +:+       +:+ +:+        +:+        +:+          +:+        +:+    +:+ +:+ +:+:+ +:+ +:+                 +:+    +:+    +:+         +:+     +:+    +:+ +:+                  +:+   +:+  +:+    +:+  +:+ +:+  +:+        +:+         
 +#+  +:+  +#+ +#++:++#   +#+        +#+          +#+        +#+    +:+ +#+  +:+  +#+ +#++:++#            +#+    +#+    +:+         +#+     +#++:++#++ +#++:++#            +#++:++#++: +#++:++#+    +#++:   +#++:++#++ +#++:++#++   
+#+ +#+#+ +#+ +#+        +#+        +#+          +#+        +#+    +#+ +#+       +#+ +#+                 +#+    +#+    +#+         +#+     +#+    +#+ +#+                 +#+     +#+ +#+    +#+    +#+           +#+        +#+    
#+#+# #+#+#  #+#        #+#        #+#          #+#    #+# #+#    #+# #+#       #+# #+#                 #+#    #+#    #+#         #+#     #+#    #+# #+#                 #+#     #+# #+#    #+#    #+#    #+#    #+# #+#    #+#     
###   ###   ########## ########## ##########    ########   ########  ###       ### ##########          ###     ########          ###     ###    ### ##########          ###     ### #########     ###     ########   ########       
                                                                                                                                                                                    
)";

// Function declarations
void mainMenu(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void store(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void fight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void bossFight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void rest(Player& player);

int main() {
	//Weapon info list
	Weapon DAGGER = { "DAGGER", 5, 50, false, false };
	Weapon SWORD = { "SWORD", 10, 300, false, false };
	Weapon BOW = { "SWORD", 18, 500, false, false };

	Player player;
	player.l_a = "Normal";
	player.r_a = "Normal";
	player.l_l = "Normal";
	player.r_l = "Normal";
	player.health = "Full";
	player.money = 100;
	player.energy = 100;


	cout << gameTitle << endl;
	cout << "What is your name? ";
	cin >> player.name;
	player.rank = "COPPER";

	// Start the game loop
	mainMenu(player, DAGGER, SWORD, BOW);

	return 0;
}

void mainMenu(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
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

		// Promotions based on money(requirement for boss fight)
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
		if (player.money >= 3000 && player.rank == "GOLD") {
			cout << "You have been promoted to PLATINIUM rank adventure!\n";
			player.rank = "PLATINIUM";
			Sleep(1600);
		}
		if (player.money >= 5000 && player.rank == "PLATINIUM") {
			cout << "You have been promoted to MYTHRIL rank adventure!\n";
			player.rank = "MYTHRIL";
			Sleep(1600);
		}
		if (player.money >= 10000 && player.rank == "MYTHRIL") {
			cout << "You have been promoted to ADAMANTITE rank adventure!\n";
			player.rank = "ADAMANTITE";
			Sleep(1600);
		}

		// Display player info
		cout << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " dollars. Energy: " << player.energy << "\n";
		if (dagger.equipped) cout << "Weapon: DAGGER\n";
		if (sword.equipped) cout << "Weapon: SWORD\n";
		if (bow.equipped) cout << "Weapon: BOW\n";

		cout << "\nAdventure Rank: " << player.rank;
		cout << "\n\n1) Go to Store\n2) Rest\n3) Fight\n\nAction: ";

		int choice;
		while (true) {
			if (!(cin >> choice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice. Try again.\n";
				Sleep(1000);
			}
			else {
				switch (choice) {
				case 1:
					store(player, dagger, sword, bow);
					break;
				case 2:
					rest(player);
					break;
				case 3:
					fight(player, dagger, sword, bow);
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

void store(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
	while (true) {
		system("CLS");
		cout << "Welcome to the store! You have " << player.money << " $.\n";
		cout << "\n1) DAGGER | $50\n2) SWORD | $300\n3) BOW | $500 \n4) Back\n\nAction: ";

		int choice;
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
		}

		if (choice == 1) {
			if (dagger.purchased) {
				cout << "You already purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					dagger.equipped = true;
					sword.equipped = false;
					bow.equipped = false;
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
				}
				if (equipChoice == 1) {
					dagger.equipped = true;
					sword.equipped = false;
					bow.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}
		else if (choice == 2) {
			if (sword.purchased) {
				cout << "You already purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					sword.equipped = true;
					dagger.equipped = false;
					bow.equipped = false;
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
				}
				if (equipChoice == 1) {
					sword.equipped = true;
					dagger.equipped = false;
					bow.equipped = false;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}
		else if (choice == 3) {
			if (bow.purchased) {
				cout << "You already purchased the BOW. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
				int equipChoice;
				while (!(cin >> equipChoice) || (equipChoice != 1 && equipChoice != 2)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice. Please enter 1 or 2.\n";
					Sleep(1000);
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = true;
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
				}
				if (equipChoice == 1) {
					dagger.equipped = false;
					sword.equipped = false;
					bow.equipped = true;
				}
			}
			else {
				cout << "You don't have enough money.";
				Sleep(1400);
			}
		}
		else if (choice == 4) {
			break;
		}
		else {
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
		}
	}
}

void fight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
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

	if (!dagger.equipped && !sword.equipped && !bow.equipped) {
		cout << "You don't have a weapon equipped.";
		Sleep(1400);
		return;
	}

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
	player.money += enemiesKilled * 15;
	player.energy -= (enemiesKilled * 5);

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
void bossFight(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
	srand(static_cast<unsigned int>(time(0)));
	system("CLS");


	if (player.rank != "SILVER" || player.rank != "GOLD" || player.rank != "GOLD" || player.rank != "PLATINIUM" || player.rank != "MYTHRIL" || player.rank != "ADAMANTITE") {
		cout << "You're not ready to fight the boss, rest to restore energy.";
		Sleep(1400);
		return;
	}

	if (player.l_a == "Damaged" || player.r_a == "Damaged" || player.l_l == "Damaged" || player.r_l == "Damaged") {
		cout << "You're injured, rest to heal.";
		Sleep(1400);
		return;
	}

	if (player.energy < 100) {
		cout << "You're not ready to fight the boss, rest to restore energy.";
		Sleep(1400);
		return;
	}

	if (!dagger.equipped && !sword.equipped && !bow.equipped) {
		cout << "You don't have a weapon equipped.";
		Sleep(1400);
		return;
	}

	

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

	cout << "You fight, killing ";
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