#ifndef _GAME_H_
#define _GAME_H_

//Includes of required classes
#include "Monkey.h" //Parent class of all monkeys
#include "Dart.h" //Child class of monkey
#include "Bomb.h" //Child class of monkey
#include "Boomerang.h" //Child class of monkey
#include "Bloon.h" //Parent class of all bloons
#include "Basic.h" //Child class of bloon

//Includes of allowed libraries
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//************************Constants*********************
//**Constants related to starting game**
const int START_ROUND = 1; //Starting round
const int START_LIFE = 100; //Starting life (num damage before losing game)
const int START_MONEY = 10; //Starting money for player

//Constants related to the length of the path
const int PATH_LENGTH = 3; //Length of the path (could be anything)
const int START_BLOON = -1; //Starting location of all bloons

//**Constants related to money/cost**
const int COST_DART = 2; //Starting cost for dart monkey
const int COST_BOOMERANG = 4; //Starting cost for boomerang monkey
const int COST_BOMB = 6; //Starting cost for a bomb monkey
const int COST_IMPROVE = 2; //Cost for each improvement (regardless of type)
const int EARN_POP = 1; //Earnings per pop of a bloon
const int IMPROVE_VALUE = 2; //When a bloon is improved, increases the value based on this

//**Constants related to damage**
const int DAMAGE_DART = 1; //Starting damage for dart monkey
const int DAMAGE_BOOM = 1; //Starting damage for boomerage monkey
const int DAMAGE_BOMB = 1; //Starting damage for bomb monkey
//******************************************************

class Game {
public:
  // Name: Game() - Default Constructor
  // Description: Creates a new Game and populates money, round, and health
  // Preconditions: None
  // Postconditions: Initializes all game variables to defaults (constants)
  // including rounds played
  Game();
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated in Game
  ~Game();
  // Name: PrintMap()
  // Description: For each location on the path, outputs the bloons and the monkeys (or none)
  // Precondition: None
  // Postcondition: None
  void PrintMap();
  // Name: ImproveMonkey
  // Description: Asks the user which monkey they would like to improve
  //              Increases chosen monkey's damage by IMPROVE_VALUE above
  // Precondition: Must have monkeys in m_monkeys and have enough money to pay (COST_IMPROVE)
  // Postcondition: Monkey's damage is permanently improved
  void ImproveMonkey();
  // Name: BuyMonkey
  // Description: Asks the user which monkey they would like to buy
  //            Reduces m_curMoney and then calls PlaceMonkey (which creates and places new monkey)
  // Precondition: Must have enough money to pay (COST_DART, COST_BOOMERANG, or COST_BOMB)
  // Postcondition: Specified monkey is added a chosen location on the path
  void BuyMonkey();
  // Name: PlaceMonkey(int choice)
  // Description: Based on monkey purchased in BuyMonkey, asks user where to place new monkey
  //              Dynamically allocates new monkey and populates location and adds to m_monkey
  // Preconditions: Successfully purchased new monkey
  // Postconditions: New monkey is added to m_monkey at chosen location
  void PlaceMonkey(int choice);
  // Name: StartGame()
  // Description: Welcomes the player to the game. Continually calls MainMenu until user quits
  // Preconditions: None
  // Postconditions: Thanks user when quitting
  void StartGame();
  // Name: MainMenu()
  // Description: Checks to see if player still has life. If m_curLife <= 0, game ends with loss.
  //              Display menu (View Map, Buy New Monkey, Improve Existing Monkey
  //              Progress Round, Check Stats, or Quit).
  //              Calls function related to user choice.
  // Preconditions: None
  // Postconditions: Game continues until quit or player runs out of life
  int MainMenu();
  // Name: Stats()
  // Description: Displays the information about the game
  //              (current round, number of monkeys, money, and lives left)
  // Preconditions: None
  // Postconditions: None
  void Stats();
  // Name: PlayRound()
  // Description: Announces beginning and end of round
  //              Calls PopulateBloons once then ResolveBattle once.
  //              Calls RemovePopped (5 times due to erase function)
  //              Calls MoveBloons once then calls CheckPath (5 times due to erase call)
  //              Increments curRound
  // Preconditions: None
  // Postconditions: Round progresses
  void PlayRound();
  // Name: PopulateBloons
  // Description: Each round, dynamically allocated bloons added to path in position START_BLOON
  //              Bloons have a minimum of 1 health.
  //              For each round, the number of new bloons increases matching the round number
  //              For example: Round 1 = 1 red bloon (health 1)
  //              Round 2 = 1 red bloon (health 1) and 1 blue bloon (health 2)
  //              Round 3 = 1 red (health 1) and 1 blue (health 2) and 1 green (health 3)
  //              Round 4 = 1 red, 1 blue, 1 green, and 1 yellow (health 4) and so forth
  //              Notifies user that a new bloon (with color) has appeared.
  // Preconditions: Round is at least 1
  // Postconditions: All new bloons populated
  void PopulateBloons();
  // Name: ResolveBattle()
  // Description: Each monkey attacks the whole bloon vector.
  //              For each pop, curMoney is increased.
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Damage is dealt to bloons
  void ResolveBattle();
  // Name: RemovePopped()
  // Description: Iterates through m_bloons and if health is <= 0, bloon is deallocated and
  //              removed from m_bloons
  //         HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void RemovePopped();
  // Name: MoveBloons
  // Description: For each bloon that still lives, it moves one location down the path
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons increment their location
  void MoveBloons();
  // Name: CheckPath
  // Description: Iterates over m_bloons to see if location is equal to (or greater than)
  //              PATH_LENGTH. If location is equal to PATH_LENGTH, causes damage to player.
  //              Damage to player is one per health of bloon.
  //              If 10 green bloons (health 3) hit player, player takes 30 damage
  //              Bloons that hurt player are deallocated and erased from m_bloons
  //              HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void CheckPath();
private:
  vector<Bloon*> m_bloons; // Vector for holding all bloons in game
  vector<Monkey*> m_monkeys; //Vector for holding all monkeys in game
  int m_curRound; //Tracks number of rounds played in game
  int m_curMoney; //Tracks current money for upgrades
  int m_curLife; //Tracks current life. When 0, game over.
};

#endif
