#include "Game.h"



Game::Game(){
    //set m_curLife, m_curMoney, and m_curRound to the default values
    m_curLife = START_LIFE;
    m_curMoney = START_MONEY;
    m_curRound = START_ROUND;

}

Game::~Game(){
    //remove all monkeys from m_monkey
    for (unsigned int i = 0; i < m_monkeys.size(); i++){
        Monkey *monkey = m_monkeys.at(i);
        m_monkeys.erase(m_monkeys.begin() + int(i));
        delete monkey;
    }

    //set m_curLife, m_curMoney, and m_curRound to 0
    m_curLife = 0;
    m_curMoney = 0;
    m_curRound = 0;
}


void Game::PrintMap(){
    //Set Monkey iterator to monkey
    //Set Bloon iterator to bloon
    vector<Monkey*>::iterator monkey;
    vector<Bloon*>::iterator bloon;

    //iterate through each location
    for (int i = 0; i < PATH_LENGTH; i++){
        //set monkeyCount and bloonCount to 0
        int monkeyCount = 0;
        int bloonCount = 0;

        //Print out Location
        cout << "**Location " << i+1 << "**" <<endl;

        cout << "--Monkeys--" << endl;
        
        //iterate through m_monkey and print out every monkey that is in the current locaiton
        for(monkey = m_monkeys.begin(); monkey < m_monkeys.end(); monkey++){
            Monkey *myMonkey = *monkey;
            if (myMonkey->GetLocation() == i){
                cout << myMonkey->GetLocation()+1 << ". " << *myMonkey << endl;
                monkeyCount++;
            }
        }
        
        //if monkeyCount is 0, that means there are no monkeys
        //print none
        if (monkeyCount == 0){
            cout << "None" << endl;
        }


        cout << "<<Bloons>>" << endl;

        //iterate through all the bloons in m_bloons and print out each bloon in the
        //current location
        for(bloon = m_bloons.begin(); bloon < m_bloons.end(); bloon++){
            Bloon *myBloon = *bloon;
            if (myBloon->GetLocation() == i){
                cout << *myBloon << endl;
                bloonCount++;
            }
        }

        //if bloonCount is 0, that means no bloons and print none
        if (bloonCount == 0){
            cout << "None" << endl;
        }
        cout << endl;
    }



}

void Game::ImproveMonkey(){
    //The number of monkeys in m_monkeys
    int numberOfMonkeys = int(m_monkeys.size());

    if (numberOfMonkeys > 0){
        //Set Monkey iterator to monkey
        vector<Monkey*>::iterator monkey;

        int userInput;

        int count = 1;

        //temp monkey called myMonkey
        Monkey *myMonkey;

        cout << "Which monkey would you like to improve (1-" << numberOfMonkeys << "?" << endl;

        //iterate through each monkey and and print them out
        for(monkey = m_monkeys.begin(); monkey < m_monkeys.end(); monkey++){
            myMonkey = *monkey;
            cout << count <<"." << *myMonkey << endl;
            count++;
        }

        //store user input in UserInput
        cin >> userInput;

        //check the user input
        while (userInput < 1 || userInput > numberOfMonkeys){
            cout << "Choose between 1-" << numberOfMonkeys << endl;
            cin.ignore(128,'\n');
            cin >> userInput;
        }

        //subtract 1 for indexing
        userInput -= 1;

        //check if the user has the money to improve
        if(m_curMoney >= COST_IMPROVE){
            
            //get the monkey the user wanted to improve
            myMonkey = m_monkeys.at(userInput);
            
            //increase the monkey's damage by IMPROVE_VALUE
            myMonkey->SetDamage(myMonkey->GetDamage() + IMPROVE_VALUE);

            //tell the user what happend
            cout << myMonkey->GetType() <<" in position " << myMonkey->GetLocation() + 1 << " improved!" << endl;
        
        //user has no money, tell them that
        }else{
            cout << "Not enough money to buy improvement" << endl;
        }

    //tell the user they need to buy monkeys before improving them
    }else{
        cout << "You need to buy monkeys before improving them" << endl;
    }

    


}

void Game::BuyMonkey(){
    int userInput;

    cout << "What type of monkey would you like to buy?" << endl;
    cout << "1. Dart Monkey" << endl;
    cout << "2. Boomerang Monkey" << endl;
    cout << "3. Bomb Monkey" << endl;
    cout << "4. Cancel" << endl;

    cin >> userInput;

    //check user input
    while (userInput < 1 || userInput > 4){
        cin.ignore(128,'\n');
        cout << "What type of monkey would you like to buy?" << endl;
        cout << "1. Dart Monkey" << endl;
        cout << "2. Boomerang Monkey" << endl;
        cout << "3. Bomb Monkey" << endl;
        cout << "4. Cancel" << endl;
        cin >> userInput;
    }

    //depending on userInput, check if the user has money
    //to buy chosen monkey. if not, return nothing to stop
    //the function from continuing
    switch (userInput){
        case 1:
            if(m_curMoney < COST_DART){
                cout << "not enough money to buy Dart Monkey" << endl;
                return;
            }
            break;
        case 2:
            if(m_curMoney < COST_BOOMERANG){
                cout << "not enough money to buy Boomerang Monkey" << endl;
                return;
            }
            break;
        case 3:
            if(m_curMoney < COST_BOMB){
                cout << "not enough money to buy Bomb Monkey" << endl;
                return;
            }
            break;
        case 4:
            return;
            break;

    }

    //User has the money, call PlaceMonkey
    PlaceMonkey(userInput);

}

void Game::PlaceMonkey(int choice){
    int userLocation;

    //ask the user where to place monkey
    cout << "Where would you like to place the new monkey? (1-" << PATH_LENGTH << ")" << endl;
    cin >> userLocation;

    //check user input
    while (userLocation < 1 || userLocation > PATH_LENGTH){
        cout << "Where would you like to place the new monkey? (1-" << PATH_LENGTH << ")" << endl;
        cin.ignore(128,'\n');
        cin >> userLocation;
    }

    //subtract one for indexing
    userLocation -= 1;
    
    //depending on user's choice, buy the monkey the user
    //wanted and add it to list of monkeys
    switch (choice){
        case 1:
            m_monkeys.push_back(new Dart("Dart",DAMAGE_DART, userLocation));
            m_curMoney -= COST_DART;
            cout << "New Dart monkey placed in location " << userLocation + 1 << endl;
            break;
        case 2:
            m_monkeys.push_back(new Boomerang("Boomerang",DAMAGE_BOOM, userLocation));
            m_curMoney -= COST_BOOMERANG;
            cout << "New Boomerang monkey placed in location " << userLocation + 1 << endl;
            break;
        case 3:
            m_monkeys.push_back(new Bomb("Bomb",DAMAGE_BOMB, userLocation));
            m_curMoney -= COST_BOMB;
            cout << "New Boomerang monkey placed in location " << userLocation + 1 << endl;
            break;
    }
    
}

void Game::StartGame(){
    bool gameOver = false;

    cout << "Welcome to UMBC Bloons!" << endl;
    
    //while gameOver is false, call MainMenu
    while (gameOver == false){
        int userChoice = MainMenu();
        
        switch (userChoice){
            case 1:
                PrintMap();
                break;
            case 2:
                BuyMonkey();
                break;
            case 3:
                ImproveMonkey();
                break;
            case 4: 
                PlayRound();
                break;
            case 5:
                Stats();
                break;
            case 6:
                gameOver = true;
                break;
        }
    }

}

int Game::MainMenu(){

    //check if the user still can play, if not, end the game by return 6
    if (m_curLife <= 0){
        cout << "No more life, gameOver" << endl;
        cout << "Thanks for playing" << endl;
        return 6;
    }

    int userInput;

    cout << "What would you like to do?" << endl;
    cout << "1. View Map" << endl;
    cout << "2. Buy New Monkey" << endl;
    cout << "3. Improve Existing Monkey" << endl;
    cout << "4. Progress Round" << endl;
    cout << "5. Check Stats" << endl;
    cout << "6. Quit" << endl;

    cin >> userInput;

    //check userInput
    while (userInput < 1 || userInput > 6){
        cin.ignore(128,'\n');

        cout << "What would you like to do?" << endl;
        cout << "1. View Map" << endl;
        cout << "2. Buy New Monkey" << endl;
        cout << "3. Improve Existing Monkey" << endl;
        cout << "4. Progress Round" << endl;
        cout << "5. Check Stats" << endl;
        cout << "6. Quit" << endl;

        cin >> userInput;
    }

    //return userInput
    return userInput;
}

void Game::Stats(){
    //Prints out all the stats for the user
    cout << "**CURRENT STATS**" << endl;
    cout << "Current Round: " << m_curRound << endl;
    cout << "Monkeys Working: " << int(m_monkeys.size()) << endl;
    cout << "Current Money: " << m_curMoney << endl;
    cout << "Current Life: " << m_curLife <<endl;

}

void Game::PlayRound(){
    //Tells the user that the round is starting
    cout << "Starting Round " << m_curRound << endl;


    //Calss PopulateBloons and ResolveBattle
    PopulateBloons();
    ResolveBattle();


    //Calss RemovedPopped 5 times
    for (int i = 5; i > 0; i--){
        RemovePopped();
    }

    //Calls MoveBloons
    MoveBloons();

    //Calls CheckPath 5 times
    for (int i = 5; i > 0; i--){
        CheckPath();
    }


    //Tells the user that the round has ended
    cout << "Round " << m_curRound << " Completed" << endl;

    //Increase m_curRound by 1
    m_curRound++;


}

void Game::PopulateBloons(){
    //bloonHealth always starts as one
    int bloonHealth = 1;

    //for each round, add a bloon and increase bloonHealth
    for (int i = 0; i < m_curRound; i++){
        Basic *bloon = new Basic(bloonHealth,START_BLOON);
        m_bloons.push_back(bloon);
        cout << "A new " << bloon->GetColor() << " bloon appears!" << endl;
        bloonHealth++;
    }

}

void Game::ResolveBattle(){
    //Set Monkey iterator to monkey
    vector<Monkey*>::iterator monkey;

    //iterate through each monkey and call Attack
    for(monkey = m_monkeys.begin(); monkey < m_monkeys.end(); monkey++){
        Monkey *myMonkey = *monkey;
        
        m_curMoney += myMonkey->Attack(m_bloons);
    }

}

void Game::RemovePopped(){

    //Set Bloon iterator to bloon
    vector<Bloon*>::iterator bloon;
    int counter = 0;

    //iterate through each bloon and check if their still alive,
    //if not, erase them from m_bloon and delete them
    //increase counter for each loop
    for(bloon = m_bloons.begin(); bloon < m_bloons.end(); bloon++){
        Bloon *myBloon = *bloon;
        if (myBloon->GetHealth() <= 0){
            m_bloons.erase(m_bloons.begin() + counter);
            delete myBloon;
        }
        counter++;
    }

}

void Game::MoveBloons(){
    //Set Bloon iterator to bloon
    vector<Bloon*>::iterator bloon;

    //Iterate through each bloon and check if their alive, if so
    //increase location by 1
    for(bloon = m_bloons.begin(); bloon < m_bloons.end(); bloon++){
        Bloon *myBloon = *bloon;
        if (myBloon->GetHealth() > 0){
            myBloon->SetLocation(myBloon->GetLocation() + 1);
        }
    }

    //tell the user what happened
    cout << "The bloons move along the path" << endl;
}

void Game::CheckPath(){
    //Set Bloon iterator to bloon
    vector<Bloon*>::iterator bloon;

    int counter = 0;
    
    //iterate through each bloon and check if they reached the end
    //if so, reduce m_curLife by the health of the bloon and erase
    //them from m_bloons and delete them as well
    for(bloon = m_bloons.begin(); bloon < m_bloons.end(); bloon++){
        Bloon *myBloon = *bloon;
        if (myBloon->GetLocation() >= PATH_LENGTH){
            m_curLife -= myBloon->GetHealth();
            m_bloons.erase(m_bloons.begin() + counter);
            delete myBloon;
        }
        counter++;
    }
}