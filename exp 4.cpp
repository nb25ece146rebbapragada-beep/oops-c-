#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

// =========================
// COLORS
// =========================

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// =========================
// RANDOM NUMBER GENERATOR
// =========================

random_device rd;
mt19937 rng(rd());

int randomNumber(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// =========================
// PLAYER
// =========================

struct Player
{
    string name;

    int health = 100;
    int maxHealth = 100;

    int attack = 20;
    int coins = 0;

    int potions = 2;
    int keys = 0;

    int score = 0;

    bool hasSword = false;
    bool hasShield = false;
};

// =========================
// UTILITIES
// =========================

void slowPrint(string text, int delay = 15)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }

    cout << endl;
}

void line()
{
    cout << CYAN
         << "\n============================================\n"
         << RESET;
}

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

void pauseGame()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

// =========================
// PLAYER STATUS
// =========================

void showStatus(Player &p)
{
    line();

    cout << BOLD << "PLAYER: " << p.name << RESET << "\n";

    cout << RED
         << "❤️  HP: "
         << p.health
         << "/"
         << p.maxHealth
         << RESET << "\n";

    cout << YELLOW
         << "💰 Coins: "
         << p.coins
         << RESET << "\n";

    cout << GREEN
         << "🧪 Potions: "
         << p.potions
         << RESET << "\n";

    cout << BLUE
         << "🗝️  Keys: "
         << p.keys
         << RESET << "\n";

    cout << MAGENTA
         << "🏆 Score: "
         << p.score
         << RESET << "\n";

    cout << "⚔️  Attack: " << p.attack << "\n";

    if (p.hasSword)
        cout << "🗡️ Sword equipped\n";

    if (p.hasShield)
        cout << "🛡️ Shield equipped\n";

    line();
}

// =========================
// INTRO
// =========================

void intro()
{
    clearScreen();

    cout << RED << BOLD;

    cout << R"(

███████╗███████╗ ██████╗ █████╗ ██████╗ ███████╗
██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝
█████╗  ███████╗██║     ███████║██████╔╝█████╗
██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██╔══╝
███████╗███████║╚██████╗██║  ██║██║     ███████╗
╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚══════╝

        ████████╗██╗  ██╗███████╗
        ╚══██╔══╝██║  ██║██╔════╝
           ██║   ███████║█████╗
           ██║   ██╔══██║██╔══╝
           ██║   ██║  ██║███████╗
           ╚═╝   ╚═╝  ╚═╝╚══════╝

)";

    cout << RESET;

    slowPrint("The mansion has been abandoned for 73 years...");
    slowPrint("Tonight, you decided to enter.");
    slowPrint("That was your first mistake.");

    cout << "\n";

    slowPrint("The front door suddenly SLAMS shut behind you.");

    cout << RED << "\nSomething whispers from upstairs...\n" << RESET;

    pauseGame();
}

// =========================
// RANDOM EVENT
// =========================

void randomEvent(Player &p)
{
    int event = randomNumber(1, 5);

    line();

    switch (event)
    {
        case 1:
            cout << GREEN;
            slowPrint("✨ You found a hidden treasure chest!");
            cout << "You found 25 coins!\n";
            p.coins += 25;
            p.score += 50;
            cout << RESET;
            break;

        case 2:
            cout << RED;
            slowPrint("👻 A ghost suddenly appears!");
            slowPrint("\"GET OUT...\"");
            cout << "You lose 15 HP!\n";
            p.health -= 15;
            cout << RESET;
            break;

        case 3:
            cout << BLUE;
            slowPrint("🧪 You discover an abandoned medical cabinet.");
            cout << "You found a potion!\n";
            p.potions++;
            cout << RESET;
            break;

        case 4:
            cout << YELLOW;
            slowPrint("🪙 You find coins underneath an old carpet.");
            int coins;
            coins = randomNumber(5, 20);
            cout << "You found " << coins << " coins!\n";
            p.coins += coins;
            cout << RESET;
            break;

        case 5:
            cout << MAGENTA;
            slowPrint("🕯️ The candles suddenly go out.");

            slowPrint("You hear footsteps behind you...");

            if (randomNumber(1, 2) == 1)
            {
                cout << "Nothing happens.\n";
            }
            else
            {
                cout << RED << "Something scratches your back!\n";
                cout << "You lose 10 HP!\n" << RESET;
                p.health -= 10;
            }

            cout << RESET;
            break;
    }

    pauseGame();
}

// =========================
// COMBAT
// =========================

bool fight(Player &p, string enemy, int enemyHP, int enemyAttack)
{
    clearScreen();

    cout << RED << BOLD;
    cout << "\n        ⚔️ BATTLE ⚔️\n";
    cout << RESET;

    slowPrint("A " + enemy + " appears!");

    cout << "\n";

    while (enemyHP > 0 && p.health > 0)
    {
        cout << "\n";
        cout << RED << enemy
             << " HP: "
             << enemyHP
             << RESET << "\n";

        cout << GREEN
             << p.name
             << " HP: "
             << p.health
             << RESET << "\n";

        cout << "\n";

        cout << "1. ⚔️ Attack\n";
        cout << "2. 🛡️ Defend\n";
        cout << "3. 🧪 Use Potion\n";
        cout << "4. 🏃 Run\n";

        cout << "\nChoose: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int damage = randomNumber(p.attack - 5, p.attack + 10);

            if (p.hasSword)
            {
                damage += 15;
            }

            cout << YELLOW
                 << "\n⚔️ You attack the "
                 << enemy
                 << " for "
                 << damage
                 << " damage!\n"
                 << RESET;

            enemyHP -= damage;
        }

        else if (choice == 2)
        {
            int damage = randomNumber(1, enemyAttack / 2);

            if (p.hasShield)
                damage /= 2;

            cout << BLUE
                 << "\n🛡️ You defend!\n"
                 << "You take only "
                 << damage
                 << " damage.\n"
                 << RESET;

            p.health -= damage;

            continue;
        }

        else if (choice == 3)
        {
            if (p.potions > 0)
            {
                p.potions--;

                int heal = randomNumber(20, 35);

                p.health += heal;

                if (p.health > p.maxHealth)
                    p.health = p.maxHealth;

                cout << GREEN
                     << "\n🧪 You drink a potion and recover "
                     << heal
                     << " HP!\n"
                     << RESET;
            }
            else
            {
                cout << RED
                     << "\nYou don't have any potions!\n"
                     << RESET;
            }

            continue;
        }

        else if (choice == 4)
        {
            if (randomNumber(1, 2) == 1)
            {
                cout << YELLOW
                     << "\n🏃 You escaped!\n"
                     << RESET;

                return true;
            }
            else
            {
                cout << RED
                     << "\nYou tried to escape...\n"
                     << "BUT THE MONSTER CAUGHT YOU!\n"
                     << RESET;
            }
        }

        else
        {
            cout << "Invalid choice!\n";
            continue;
        }

        // Enemy attacks
        if (enemyHP > 0)
        {
            int damage = randomNumber(enemyAttack - 5,
                                      enemyAttack + 5);

            if (p.hasShield)
            {
                damage /= 2;

                cout << BLUE
                     << "🛡️ Your shield reduced the damage!\n"
                     << RESET;
            }

            p.health -= damage;

            cout << RED
                 << "👹 The "
                 << enemy
                 << " attacks you for "
                 << damage
                 << " damage!\n"
                 << RESET;
        }
    }

    if (p.health <= 0)
    {
        cout << RED << BOLD;

        cout << R"(

██████╗ ███████╗ █████╗ ████████╗██╗  ██╗
██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║  ██║
██║  ██║█████╗  ███████║   ██║   ███████║
██║  ██║██╔══╝  ██╔══██║   ██║   ██╔══██║
██████╔╝███████╗██║  ██║   ██║   ██║  ██║
╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝

)";

        cout << RESET;

        slowPrint("The darkness consumes you...");

        return false;
    }

    cout << GREEN << BOLD;
    slowPrint("\n🎉 YOU DEFEATED THE " + enemy + "!");
    cout << RESET;

    p.score += 100;

    return true;
}

// =========================
// SHOP
// =========================

void shop(Player &p)
{
    clearScreen();

    cout << YELLOW << BOLD;

    cout << R"(

      🧙 MYSTERIOUS SHOP 🧙

    "I sell things you probably
     shouldn't be buying."

)";

    cout << RESET;

    cout << "💰 Your coins: " << p.coins << "\n\n";

    cout << "1. 🧪 Potion      - 15 coins\n";
    cout << "2. 🗡️ Sword       - 50 coins\n";
    cout << "3. 🛡️ Shield      - 40 coins\n";
    cout << "4. ❌ Leave\n";

    cout << "\nChoose: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        if (p.coins >= 15)
        {
            p.coins -= 15;
            p.potions++;

            cout << GREEN
                 << "Potion purchased!\n"
                 << RESET;
        }
        else
            cout << RED << "Not enough coins!\n" << RESET;
    }

    else if (choice == 2)
    {
        if (p.hasSword)
        {
            cout << "You already have a sword!\n";
        }
        else if (p.coins >= 50)
        {
            p.coins -= 50;
            p.hasSword = true;

            cout << GREEN
                 << "🗡️ You bought a legendary sword!\n"
                 << RESET;
        }
        else
            cout << RED << "Not enough coins!\n" << RESET;
    }

    else if (choice == 3)
    {
        if (p.hasShield)
        {
            cout << "You already have a shield!\n";
        }
        else if (p.coins >= 40)
        {
            p.coins -= 40;
            p.hasShield = true;

            cout << GREEN
                 << "🛡️ You bought a shield!\n"
                 << RESET;
        }
        else
            cout << RED << "Not enough coins!\n" << RESET;
    }

    pauseGame();
}

// =========================
// FINAL BOSS
// =========================

bool finalBoss(Player &p)
{
    clearScreen();

    cout << MAGENTA << BOLD;

    cout << R"(

        ██████╗  ██████╗ ███╗   ███╗ ██████╗ ███╗   ██╗
        ██╔══██╗██╔═══██╗████╗ ████║██╔═══██╗████╗  ██║
        ██║  ██║██║   ██║██╔████╔██║██║   ██║██╔██╗ ██║
        ██║  ██║██║   ██║██║╚██╔╝██║██║   ██║██║╚██╗██║
        ██████╔╝╚██████╔╝██║ ╚═╝ ██║╚██████╔╝██║ ╚████║
        ╚═════╝  ╚═════╝ ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

                    THE HOUSE OWNER

)";

    cout << RESET;

    slowPrint("You finally reach the basement.");
    slowPrint("There is a throne made of bones.");
    slowPrint("Something sits on it.");

    cout << RED << "\nTHE HOUSE OWNER:\n" << RESET;

    slowPrint("\"You should never have come here.\"");

    pauseGame();

    return fight(p, "HOUSE OWNER 👹", 180, 25);
}

// =========================
// MAIN GAME
// =========================

int main()
{
    Player player;

    intro();

    clearScreen();

    cout << CYAN
         << "Enter your name: "
         << RESET;

    getline(cin, player.name);

    if (player.name.empty())
        player.name = "Hero";

    clearScreen();

    slowPrint("Welcome, " + player.name + "...");

    slowPrint("Your goal is simple:");

    cout << YELLOW << BOLD;
    slowPrint("ESCAPE THE HOUSE ALIVE.");
    cout << RESET;

    pauseGame();

    // =========================
    // ROOM 1
    // =========================

    clearScreen();

    cout << BOLD << "🏚️ ROOM 1 — THE FOYER\n" << RESET;

    slowPrint("The entrance hall is covered in dust.");

    randomEvent(player);

    // =========================
    // MAIN GAME LOOP
    // =========================

    bool basementUnlocked = false;

    while (player.health > 0 && !basementUnlocked)
    {
        clearScreen();

        line();

        cout << BOLD
             << "🏚️ THE HAUNTED HOUSE\n"
             << RESET;

        line();

        cout << "1. 🚪 Explore Library\n";
        cout << "2. 🕯️ Explore Bedroom\n";
        cout << "3. 🧪 Visit Shop\n";
        cout << "4. 📊 Check Status\n";
        cout << "5. 🚪 Try Basement Door\n";

        cout << "\nChoose: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            clearScreen();

            cout << BLUE
                 << "📚 THE LIBRARY\n"
                 << RESET;

            slowPrint("Books cover every wall.");

            int event = randomNumber(1, 3);

            if (event == 1)
            {
                slowPrint("You find a hidden key!");

                player.keys++;
                player.score += 50;

                cout << GREEN
                     << "🗝️ Key obtained!\n"
                     << RESET;
            }
            else
            {
                fight(player,
                      "Library Phantom 👻",
                      60,
                      15);
            }

            pauseGame();
        }

        else if (choice == 2)
        {
            clearScreen();

            cout << MAGENTA
                 << "🛏️ THE BEDROOM\n"
                 << RESET;

            slowPrint("The bed moves by itself.");

            int event = randomNumber(1, 3);

            if (event == 1)
            {
                slowPrint("You found 30 coins underneath the bed!");

                player.coins += 30;
                player.score += 30;
            }
            else
            {
                fight(player,
                      "Creepy Doll 🪆",
                      50,
                      12);
            }

            pauseGame();
        }

        else if (choice == 3)
        {
            shop(player);
        }

        else if (choice == 4)
        {
            clearScreen();
            showStatus(player);
            pauseGame();
        }

        else if (choice == 5)
        {
            clearScreen();

            cout << RED
                 << "🚪 THE BASEMENT DOOR\n"
                 << RESET;

            if (player.keys >= 2)
            {
                slowPrint("You insert the keys...");

                slowPrint("CLICK.");

                slowPrint("The door opens.");

                basementUnlocked = true;

                pauseGame();
            }
            else
            {
                slowPrint("The door is locked.");

                cout << YELLOW
                     << "You need 2 keys.\n"
                     << "You currently have: "
                     << player.keys
                     << "\n"
                     << RESET;

                pauseGame();
            }
        }

        else
        {
            cout << RED << "Invalid choice!\n" << RESET;
        }
    }

    // =========================
    // BOSS
    // =========================

    if (player.health > 0)
    {
        bool won = finalBoss(player);

        if (won && player.health > 0)
        {
            clearScreen();

            cout << GREEN << BOLD;

            cout << R"(

███████╗ ██████╗ █████╗ ██████╗ ███████╗██████╗
██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
█████╗  ██║     ███████║██████╔╝█████╗  ██║  ██║
██╔══╝  ██║     ██╔══██║██╔═══╝ ██╔══╝  ██║  ██║
███████╗╚██████╗██║  ██║██║     ███████╗██████╔╝
╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚══════╝╚═════╝

                    🏆 YOU ESCAPED! 🏆

)";

            cout << RESET;

            slowPrint("The mansion collapses behind you.");

            slowPrint("You survived the Haunted House!");

            cout << "\n";
            cout << YELLOW << BOLD;

            cout << "FINAL SCORE: "
                 << player.score
                 << "\n";

            cout << RESET;

            if (player.score >= 400)
            {
                cout << GREEN
                     << "\n🏆 LEGENDARY SURVIVOR!\n"
                     << RESET;
            }
            else if (player.score >= 250)
            {
                cout << CYAN
                     << "\n⭐ BRAVE SURVIVOR!\n"
                     << RESET;
            }
            else
            {
                cout << YELLOW
                     << "\n😅 YOU BARELY SURVIVED!\n"
                     << RESET;
            }
        }
    }

    cout << "\n";
    cout << CYAN
         << "Thanks for playing, "
         << player.name
         << "! 👻\n"
         << RESET;

    return 0;
}