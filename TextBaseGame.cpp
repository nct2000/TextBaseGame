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

//Game title + logo
const char* gameTitle = R"(
                 : .::;;;;;+XX:    :$&&&&&&&&&&&&&&&&&&$+.                 .....   .+xx: ....  .+::::.:::: :.+$$x.    ;XXX$:....:;$$$$$$$$$$XX$Xx;;;;;+xX$&&&&&&&&&&&&$$$$$$$$$$$$$$XXXx+;;;+xX$&&&        
                   .:::;;;.  :x&&&&&&&&&&&&&&&&&&&&&&&&x:                         ... +xx:. ;:;+X+:::::;;x++;;$$$$.     +$$$+...;XXXXXXXXXx;;;;;;+;    ;$$$$&&&&&&&&&&&&&&&&&$$$$$$$$$$$XXXXXX$$$&&        
                   .:;;;  x$$$$$$$&$$&&&&&&&&&&&&&$$$&&&;.                             +XXX+:x+$$$xX:+++x$$X+$$$&&&:      X$X$;:$XxxxXXxxx+:..;+XX$X..;$$$&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$&&&        
                  .::;. X$XX$$&&&&&$$XX$&&&&&&&&$x++xX$&$X                              .xXXXX$$$$$$$$$$$$$&$&&&&&&&x . .. .$$$$&$$Xx;xxx+;.:;xX$$&$X$XXXXX$$$$$&&&&&&&&&&&&&&&&&&&&&&$$$$&$$$$$&&&        
                  .:: x$x++$$$$$$$$$$XxxX$$&&&$Xxx+;;;XX$&$.             :              . xXX$$$$$$$$$$&$&$&&&&&&&&&&&x:     ;$$$&&+ $Xx+;.:;xXX$&&&$$$$X$X..:+x$$$$$$&&&&&&&&&&&&&&&&&&$$$&&&&&&&&        
                  ..:$X+:;xXxx++xxxx$xx++X$$&Xxxxx++;;;XX$&&; .     .    :       +;       .+$$$$$$$$$&$&&&&$&&&&X+xx$&&&+      .X$X$$&$X+;:+xXXX&$XX&&&&&$$;..   .;+xxxXXx$$&&&&&&&&&&&&&&&&&&&&&&&        
                   +xx+  ;;X     .::X;;:.+xX$xx++++;::..XX$&$:    :.;   .:        .   .     ;X$$$$$$&&&&&&&&&&X;:+xxxx$&&&+ .;$$XX$$$$&$x++xxXX&Xx+$&&&&&&&&$$+:..    .::;;++x+X$$$$$&&&&&&&&&&&&&&        
                 .++++. ..                +xXx+;;;;: ...+X+&&X:  : . .  ;$        x     . :.  .;X&$+&&+$&&&&X.  .;+xxxX&&&&;x&$+xX$$$X$x+x$$$$&&++&&&&&&&&&&&$&&$$x;;:        +X$$$$&&&&&&&&&&&&&&&        
                ;::;;:       ...:::x;;;.  +xx+;;;:.   ::$X:&&&X+; :;::.;..$X:.     X     .;:.+   .x+$&+Xx:      :;++++x$&&&xX&$+::x$$Xx+;X&&&&&:x:$&&&&&&&&&&$&&&&&&X;;;:.  .+xXXxxX$$&&&&&&&&&&&&&        
              .. ..:.     ;.:;;++++Xxx+;:  xxx:.     :;XX:x&&&&&&$xx+:.::.+.Xx.     X+     :Xx.; .;Xx&:+        .:;+x+xX$&&&&&&X .:XXXx+xx$$&&& x.$$$&&&&&&X&&&&&&&&&&&&$XX;+X$X  xXX$&&&&&&&&&&&&&        
                         :+;++xXxxX$XXXx;. .$:.       .X$+&&&&&&&&&&&&$$XXxX;:x$:    XX      ;XX;;;++X:+        :;;+++xx++X$&&&&x+;;;;;+xXX$$$$X;x+$$$$&&&XX&$&&&&&&&&&&&&&&$$$$x;XX$$$$&&&&&&&&&&&        
                        .:++xxXXXX$$$$XX+.            :Xx:&&&&&&&&&&&&&&&&&&&X;;+&x:: +$X      ;XX+;+:;;.        :;;++;+X$$&&&&&&&&$X;:.:+xXxXXXXXX$X$&&&$$$$Xx$&&&&&&&&&&&&&&$XXXX$$$$$$$&&&&&&&&&        
                         +++xxXXXX$$$$XXx;.           +Xx.&&&&&&&&&&&&&&&&&$$$&X;X&+::::X&X      xxx+.xx;       .:::+:X$$$$&&$$&&$XX+++xX+:.:;;++x+;xX$$&&$$$$$+&&&&&&&&&&&&&;::;+xxXX$$&&&&&&&&&&&        
                         +:++xXXXX$&$$$Xx+x           ;xx.&&&&&&&&&&&&&$$$XXXXX$$&&$:;;+++&&$      ;x;;: .x. .. ..;:+$$$$$$$$&&$XXX+;;+X$&&$:.....:+X$X$$$&$$$$&;$&&&&&&&&&&&&;   xxXX$&&&&&&&&&&&&        
                         +.:++XXXX&$$$$X+              ;: ;&&&&&&&&&&&$$Xx;:::+x$$$&x;+xXX&&&&X          ;++;XXX$$X$$$$$$$$$&$XXxx++;++x$$&$&;:.   :xXX$$$&$$$&&&x$&&&&&&&&&&&X  .+xX$$$$&&&&&&&&&&        
                          .:;+xXX$&&$$$:           .x+.;X&&&&&&&&&&&&&$$Xx:  .;xX$$&&&Xxx$&&&&&$+     .+xxxXX$$$$&&&&&$$$&&&$x+;;;;++xxX$$$$$$..  :XX$$XXX$$$&&&&;.$$$&&&&&$&&$  .+XX&&&XX&&&&&&&&&        
                           ..:xXXX&$$$$.        .       +X;:X&&&&&&&&&$$$$XxxxX$$$$&&&&&&&&&&&&&&x  :x$X;;:;;::;+$&&&&&&&&&$$X++++++xXX$$$$$$X: .:X$$+:XXX$X$&&+ ;+$$XXXX$;$$$&.  +x$&. :XX$&&&&&&&        
                           .. +XX$&&&$$$                :X$;;$&&&&&&&&$$$$$$$$$$$$&&&&&&&&&&&&&&&&;:;$$X;+;:xXXXX+$&&&&&&&$$$$$$$XXx;;+xXxx++:+xX$$$.::$; :XX$ xx;$$XX$X::X$$$+: .;xX. X.  :$&&&&&&        
                  ...  ..   .:XXX$&$$$$$$ .               x$X::$&&&&&&&&&$&&&$&&&&&&&&&&&&&&&&&&&&&&&$&X:   ;x::;;;$&&&&&&&$$$$$$$$X+::+xX$xx$$$$$:::..::+$$X$&x.&&&$X$ +$XX$$X. .;;x:&Xxx+X$&&&&&&        
                 .::::.;;   . ;+X&$$$$$XX:                  ;x+;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$X$&&&&&$;   :::::::.+&&&&&&&&&&$$$$$$$$$$$xxX$$$X$:xx::X&$XX$$$x&&&&$$$Xx$$$x:+:+$$$Xx&X$&&&&$$$&&&        
                ..::::.+;     :;X$$$$XXx++                +$+:;+xXXX++$&&&&&&&&&&&&&&&&&&&XX&Xxx+:x$&&$$$X;   ..::::::+XXXx++xX$&&&&&&Xx$&&&&&$$&$xx::::x$XXX$X$&&&&&&&&&&&&&&$  ;XX&&&&&&&&&&&&&&&        
                ..::::;x:     :;X$XXXxx;:+     ;;     :Xx       XXx;:::;$&&&&&$x+;:::+;:+X$+++;::;;;++X&&&&&&$. .:::;:::;$$$XXXX$X+++X$$$$$$$x$&&&&&Xx:::+xXX$$X .x$:$&&&&&&&&+ ..X$$&&&&&&&&&$&&&&        
                 .::::+x:.   .:;+Xxx+;:          +   $            $$:  .x$$$x;:::. .:x;+;;: +$$$$.X;;+X&&&&&&&&&+  :;::;:  :x;.:;xXXXXXXX:;+xX$&&&&&&&$x:::+X+.:x  . :X&&&&&&&    X$$&&&&X&$$$$$&&&        
                    .:+;:    ..:;x+;.           .+   .            x.  .;;;.;;  +$&&&&&&&;     .:  X;;;X&&$$$$$&&&&;    ;+;...   X     ..;:;;+x$&&&&&&&&&$;;:X + ;.    +X&&&&X   xXX$$&&&&&&$$$$$&&&        
                     .x:.       ::.               . .   .:               .::::X$$$$$$$X$;         ::::x$$$$$$$$$&&&&       +x$XX$      .:::;;x$&&&&&&&&$X:x+x.X+ ;  .x&&&&&&.  :xXX$$$&&&&&&$$$$$&&        
                     :;:.       ..    .;;;+;xx     : .   .                ..:::.xX$XXXX.           .::X$XXXX$XXX$$$&$   .XX$:.. .; ;XX;.:::;;+$&&&&&&&X&&&$XX$:xxXXX&&&&&&&&$.   ...;X&&&&&$$$$$$$&        
                     :::            ;+xxxXXX$$$X  ..+. .:+.           ;x+;::::...x$$$X            .::;+$XXXXXXXXXxXX$   xX$. .:X+  xXX&$$$x+++xX$&&&X$&&$$&&:::x$$$&&&&&&&&&& xXxX$$X$&&&&$$&$$$$$&        
                     ;..          ;+xxXX$$$$$$&&&X .::++.+...  .:;X$$$$$$&&&&&;..:X$$$           :&$&&&;XXXXXXXXXX$X+X&&$&&$Xx.  $$$XXx$$&$&&&X$XXX$&&XX&&&&X::;X$&&&$$$&&&&&$  ..X&&&&&$$$&&$$$$$&        
                    .:           ++xXX$$$$$$$&&&&&&+;;;xxXXXXXXXXX$$$$&&&&&&&&&X:..$$&          .$&&&&&XX$XXXXXXXXX ....x&$:     .+$XXXxX&$&&&&&&&&&X+&&&&&&&. ..:;X$$$&&&&&x.;xXXxx+;+$&&&$$$$$&&&        
                    ;           .++xXX$$$$$XXX$$$&&&$xxxxXX$$$$$XXXX$$&$&&;X&&&&$;..;X.         ;&&&&&&$x$XXXXXxXX;    +&&&&++x+:::.;xXxxX$&&&&&&&&$X&&&&&&&x .:::xX&&&&&&&&&:  .....:X$&$&$$$$$$&&        
                    :           :x+xXXXX$$$$$$XxX&&&&&XxXxXXXXXX$&&&$XXx;:X: .;X&&+.  .+       :&&&&X&&&x+XXXXXxx$.   .X$&&&&&&&&$X;;:.+xxxX&&&&&&&$&&&&&&&&&&$XXX$$&&&&$&&&&&&X.....:+X$$$xXX$$$$&        
                   ...         .:X+++xx  XX$$$$+x&&&&&&&&&$x$&&x+&&&&&$;;:.xX   .   .x+..    ..$&&&;x$&&&xxXxXxXX+   ..+&&&&&&&&&&&&X;;:.;xXxX$$&$$&&&&&&&&&&&&&$;+:+$XX$&&$&&&&$:....;XXXX+XXX$$$$        
                   :          ...+:..;     $$$&::&&&&&&&&&&XX$X++&&&&&&&$   xXX    ..   ++. : &&&&&:+X&&&&X;;;:.       .$&&&&&&&&&&&&&x::. :XxxxX$&&&&&&&&&&&&&&&X:::;X$$x;;$&&&&&:.. ;xXXX$:X$x$$$        
                   .          .  .  .+XX+ ;X$$$  X&&&&&&&&&&+X$+;$&&&&&&&+  :xX$$:     ..      :&&&;$$&&&&&+ .....     .;$$$&&&&&&&&&&&&x:.. ;XxxxXX$&&&&&&&&&&&&  .;+;::+$&&&&&&&&:...xXXX$&X+$Xx$        
                                  : .xXXx xXXx.  ;&&&&&&&&&&X+X+;X&&&&&&:    +X$$$$X         .::.....x&&&&x.x;..X:      .XX$$&&&&&&&&&&&&&+.... ;XXX$XXX$&&&&&&&&  .::;:.:x$$&&&&&&&:..xXXXX$&&xX$X        
                                     +xxx x+:  .;X$&&&&&&&&&&;xx:+&&&&&$    .x .+xX&&&&$   .;+ .  +xX:..+$XX;..$Xx    x  xXX$$$&&&&&&&&&&&&$; .:...:;X$$&$&&&&&&&&&::.....;X$$&&&&&&$:.:XXXX$$&&x$&        
                                      :;.    :xX$$$$&&&&&&&&&$:x::$&&&&&.        ::.:x+X$&:;+&x  xX$X .. .......xx.  .X :X$X$$$$&&&&&&&&&&&&&+  ...;X$$&&&&&&&&&&&&&&+....:+XX$&&&&&&$..:X$$$$&$$$$        
                                           .;xxXXXX$$&&&&&&&&&+:::+&&&&X . ;:    : .:+:;xxX$$&$. .:...:.   ..++xX:;;;;x .XXXX$$$X$&&&&&$&&&&&&x::;x$$&$$&&&&&&&&&&&&&&&:   .+X$&&&&&&&$::+$$$$$$&$$        
                                   :        :;;;++xX$$&&&&&&&&$..::X&&&;   .x  +.  .:::.;;++X$&&&&$Xx.    ..;$$:.:;; X+.;XXXxX$xx$$&&&$x&&&&&&&&$$$&$+xX&$$x+$&&&&&&&&&&X...:+XX$&&&&&&X::x$$$$$$$$        
                                             ..::;+XX$&&&&&&&&&;:.:+x&&$ : :    :.: ;::..:::;;+XX$$&&&&&x   X$X...:  X$$$+.;  ;.xx;;&X+&&&&&&&&&&&&&+x$$$x;;;+$$$&&&&&&&&&+...+X$$$&&&&&X:;x$$$$$&&        
                                             ....:+xX$&&&&&&&&&;..::xx&&&x .    +    X:..+; ;.::;;;;+$$$$&$.x&$$$:    .:xX  X;:..+X$&xX$&&&&&&&&&&&&X..  :::.:x$$$$&&&&&&&&$. ..XXX$$&&&&$+;X$$$$&&        
                                            ..  .:;xX$&&&&&&&&$. ..::;;; .;x        .:XX  .x+::::;x+;;.xx$&&&&&$.   ....; .Xx;   .X$&X$XX$$$$&&&&&&&&X:::x$x. .+X$$$$$&&&&&&$ :X.;XXX$$&&$$$$$$&&&&        
                                                 :+X$$&&&&&&&&+ ...:..:     .xxX.   .:x    +;$X  :;xXX..:+x&&:+&&&&&$$Xx+ ;Xxx+xX$&&&&&XXx;::x&&&&&&&&&&&X;:+;  .+X$X$$&&&&&&&; x+:+XX$$$&$$$$$$&&&        
                                               .;xX$&&&&&&&&&:   + ....x   ;+X&$$  ...+    ;;$;  .:+&x  .;;XX .;X&&x+&$$$:;:$xX$&&&&&&X.:. +x$&&X..$&&&&&&&&&x    :xX$$$$X&&&&&$;X$xx$$$$$&&&&$$&&&        
                                              .;x$&&&&&&&&&&.    X: .:.:  :.. .&&&$.+&&    :;X   :;;$;   :;x;  :x$$$;+$$&&&&&$&&&&&&X.    x$&&$$$.;&&&&&&&&&&&&&; .  +XXX$$X$&&&$$$$+$$$$$$$&&&&&&&        
                                               +X$&&&&&&&&x     ;XX   ::  ;++xx&&&&&&&&&&X;;+$   :;+X:   +:x$...+$&&$$&&&&&&&&$&&&&x     ;$$+:x$:;&&&$&$&&&&&&&&&&x.  .;XXXX$XX$&X$$$$X+;+$$$$&&&&&        
                                          .  ..:x$$&&&&&&       ;;X.  +x.:   ; X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;+&&&&&&&X.:+&&Xxx..:;X$&;.$$$&&&&&$$$&&X.....xXX$$XX$$&&&&&$$&&&&&&&Xx        
                                            +::.;xX$&&&&:         ::     .   :;.X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$X:X&&&&&&&&&&&X.    ..;X$x.;$$$$$&$$$$$&&X. .x.+$$$X$$$$$$&&&&$&$&&&&$        
                                             .x;:;xX$&&&&&   :     +     .     ;. &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$&&&&$&&&&&&&&&&&&$$$X:  ..:xX  :$$$XXx$$X$&&&+.:$$x:+XX$$$$&$&&&&$$&$+$$        
                                      :        $+:;x$$&&&&&&;    . +      .::   . ::+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$;X:;;+&&&&&&&&&&&&&$X&&&&&&&&$:    :   ;x+++++x$$&&x;$$$x:XXX$$&$$&&&$$$x+$$$        
                                                 +;+$$&&&&&&&&&x  .+    .:. .    .   :X$$x&&&&&&&&&&&&&&&&&&&&&&$&&$x++X$:+X&&&&&&&&X&&x$&&&&&&$$$$$XXX:        .;;;xxxXXXXX$&&$$$$$$&$$$&$$X:X$$$$        
                                           .   :+  x$&&&&&&&&&&&&&;       x .:++::  .;x$;   :.X xxxX$X:.::+x    +$x:;+x$$$$&&&&&&&&&x$x&&$$$$$$$XXxxx+; +x;        .;+xxXXXX$$$$&&&&&$$$$&$$X;X$$$$        
                                      .   ;   ..:.  .X&&&&&&&&&&&&&X     .:  .  ...  :x$+  :+XX .;;;x;    +x; .:+$x.;+X&&X+$$$&&&&$&xX&&&$$$$XXXXxx;     ...:+       ...+xXXX$xX$$&&&&&$$$$$&&X+X$$        

                                                        ::::::::::: :::    ::: ::::::::::              :::     :::::::::  :::   :::  ::::::::   :::::::: 
                                                           :+:     :+:    :+: :+:                   :+: :+:   :+:    :+: :+:   :+: :+:    :+: :+:    :+: 
                                                          +:+     +:+    +:+ +:+                  +:+   +:+  +:+    +:+  +:+ +:+  +:+        +:+         
                                                         +#+     +#++:++#++ +#++:++#            +#++:++#++: +#++:++#+    +#++:   +#++:++#++ +#++:++#++   
                                                        +#+     +#+    +#+ +#+                 +#+     +#+ +#+    +#+    +#+           +#+        +#+    
                                                       #+#     #+#    #+# #+#                 #+#     #+# #+#    #+#    #+#    #+#    #+# #+#    #+#     
                                                      ###     ###    ### ##########          ###     ### #########     ###     ########   ########       
                                                                                                                                                                                    
)";

//Short story
const char* story = R"(You are an adventurer in a vast world where dungeons hold untold treasures and unspeakable horrors. For years, whispers have circulated about the Abyss dungeon, a place where the earth itself seems to tremble, and the very darkness devours all light. No one has ever returned from its depths, but that has never stopped those daring enough to seek glory and power.

You've trained for this moment your entire life, honing your skills as a warrior, mastering the use of Divine Art, and preparing to face whatever the Abyss throws at you. Your goal is simple: Enter the dungeon, face its horrors, and slay the Overlord an ancient being so powerful that even the gods tremble in fear at the thought of it.

As you stand before the entrance, the dungeon great stone door slowly creaks open, as if it has been waiting for you. The air is thick with the scent of decay, and an unnatural chill hangs in the air.)";

//The Overlord speaks
const char* bossSpeak = R"(Foolish mortal, you think your light will save you? It will flicker and die, just like the others.)";

//Player dialog
const char* playerWin = R"(The light will never die, and neither will I.)";


// Function declarations
void mainMenu(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void displayPlayerInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
void displayShopInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow);
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

	system("Color 0C");

	cout << gameTitle << endl;
	cout << story << endl;
	cout << "\nWhat is your name? ";
	cin >> player.name;
	player.rank = "BRONZE";

	// Start the game loop
	mainMenu(player, DAGGER, SWORD, BOW);

	return 0;
}

// Display player info
void displayPlayerInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
	cout << "Name: " << player.name << ". Health: " << player.health << ". Money: " << player.money << " dollars. Energy: " << player.energy << "\n";
	if (dagger.equipped) cout << "\nWeapon: DAGGER\n";
	if (sword.equipped) cout << "\nWeapon: SWORD\n";
	if (bow.equipped) cout << "\nWeapon: BOW\n";

	cout << "\nAdventure Rank: " << player.rank;
	cout << "\n\n1) Go to Store\n2) Rest\n3) Fight\n\nAction: ";
}

// Display shop info
void displayShopInfo(Player& player, Weapon& dagger, Weapon& sword, Weapon& bow) {
	cout << "Welcome to the store! You have " << player.money << " $.\n";
	cout << "\n1) DAGGER | $50\n2) SWORD | $300\n3) BOW | $500 \n4) Back\n\nAction: ";
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

		displayPlayerInfo(player, dagger, sword, bow);

		int choice;
		while (true) {
			if (!(cin >> choice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice. Try again.\n";
				Sleep(1000);
				system("CLS");
				displayPlayerInfo(player, dagger, sword, bow);
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
		displayShopInfo(player, dagger, sword, bow);

		int choice;
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Try again.\n";
			Sleep(1000);
			system("CLS");
			displayShopInfo(player, dagger, sword, bow);
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
					system("CLS");
					displayShopInfo(player, dagger, sword, bow);
					cout << "You already purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
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
					system("CLS");
					displayShopInfo(player, dagger, sword, bow);
					cout << "You've purchased the DAGGER. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
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
					system("CLS");
					displayShopInfo(player, dagger, sword, bow);
					cout << "You already purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
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
					system("CLS");
					displayShopInfo(player, dagger, sword, bow);
					cout << "You've purchased the SWORD. Would you like to equip it?\n\n1) Yes\n2) No\n\nAction: ";
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