#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;


//Global Constant Variables
const int GRID_X = 10;
const int GRID_Y = 10;
const string NOT_CHECKED = "$  ";
const string CHECKED = "G  ";


void resetGrid(string grid[GRID_Y][GRID_X]);

void displayGrid(string grid[GRID_Y][GRID_X]);

bool guessLocation(int balX, int balY, string grid[GRID_Y][GRID_X]);

void addG(int x, int y, string grid[GRID_Y][GRID_X]);

int startBalloon(int x);

int userChoice();

void checkDirection(int x, int y, int balX, int balY);

bool countinuePlaying(int balX, int balY, string grid[GRID_Y][GRID_X]);

int main()
{

    // declaration of variables
    bool gameOver = false;
    bool playAgain = false;
    int userInput = 0;

    //the multidimensional array 
    string grid[GRID_Y][GRID_X];

    //seeds rand function
    srand(time(NULL));

    // Start Balloon gives a random value. Assigned a random x and y value for the balloon.
    int balX = startBalloon(GRID_X);
    int balY = startBalloon(GRID_Y);

    
    //Reset the the multidimensional array so everything in the the multidimensional array is filled with "$"
    resetGrid(grid);

    cout << "Welcome to the Surveillance Balloon Tracker" << endl;
    cout << "You are searching for the surveillance balloon" << endl;
    
    //while the game is not Over, loop through the available choices
    while (gameOver == false){
        // UserChoice list the available choices to the user and returns a int from 1-3
        userInput = userChoice();

        //depending on the user's choice, there are three possible actions
        switch (userInput){
            case 1:
                //Display the grid
                displayGrid(grid);
                break;
            case 2: 
                //Lets the user guess the location of the balloon on the grid
                //If they get it right, guessLocation returns true which sets gameOver to true
                gameOver = guessLocation(balX, balY, grid);
                if (gameOver == true){

                    playAgain = countinuePlaying(balX,balY,grid);
                    
                    if (playAgain == true){
                        //changes the balloon's x and y coordinates
                        balX = startBalloon(GRID_X);

                        balY = startBalloon(GRID_Y);

                        gameOver = false;
                    }
                }
                break;
            case 3:
                //If the user wants to exit the game, gameOver is true and the game closes
                gameOver = true;
                cout << "Thank you for Using the Surveillance Balloon Tracker" << endl;
        }
    }
    return 0;
}

/// @brief Reset Grid takes the the multidimensional array and fills every spot with a "$"
/// @param grid the multidimensional array
void resetGrid(string grid[GRID_Y][GRID_X]){
    for(int i = 0; i < GRID_Y; i++){
        for(int j = 0; j < GRID_X; j++){
            grid[i][j] = NOT_CHECKED;
        }
    }
}


/// @brief Display Grid takes the elements from the multidimensional array and prints them out to the console
//  and prints out a count on the x and y axis
/// @param grid the multidimensional array
void displayGrid(string grid[GRID_Y][GRID_X]){

    // This for loop prints a count across the x-axis
    // and also makes sure the numbers line up correctly
    for (int i = 0; i < GRID_X; i++){

        if (i == 0){
            // if i == 0, prints out 3 spaces, zero, 1 space
            cout << "   " << i << " ";

        }else{

            if (i < 10){
                // if i < 10, print out 1 space, i, then one more space
                cout << " " << i << " ";

            }else{
                //since we enter double digits, we only print out i, then one space
                cout << i << " ";

            }
            
        }
        
    }


    cout << endl;
    
    //This loop prints a count then prints the values from the array grid
    for (int i = 0; i < GRID_Y; i++){

        //prints out the count with proper spacing
        if (i < 10){
            cout << " " << i << " ";
        }else{
            cout << i << " ";
        }
        
        //after the count is printed, print out each value in a single row from the array
        for (int j = 0; j < GRID_X; j++){
            cout << grid[i][j];
        }
        cout << endl;
    }

}


/// @brief Start Balloon returns a random value from a provide upper bound
/// @param x Max value
/// @return random value between x and 0
int startBalloon(int x){
    // x is the upper bound/maximum value
    // 0 is the minimum value
    int randValue = (rand() % ((x-1) + 1 - 0) + 0);

    return randValue;
}

/// @brief Add G is a function that simply just takes a two values and replaces
//  a value in the the multidimensional array with "G"
/// @param x user's x coordinate
/// @param y user's y coordinate
/// @param grid the multidimensional array
void addG(int x, int y, string grid[GRID_Y][GRID_X]){
    grid[y][x] = CHECKED;
}


/// @brief Asks the user for an x and y coordinate. The function then checks if the x and y
/// value is the same as the balloon's x and y values.
/// @param balX balloon's x coordinate
/// @param balY balloon's y coordinate
/// @param grid the multidimensional array 
/// @return if the user found the balloon or not.
bool guessLocation(int balX, int balY, string grid[GRID_Y][GRID_X]){
    bool foundBal = false;
    int userX = -1;
    int userY = -1;

    //This while loop validates the user's input for x value
    while (userX < 0 or userX > 19){

        cout << "Enter the X coordinate (0 - 19)" << endl;

        cin >> userX;
    }

    //This while loop validates the user's input for y value
    while (userY < 0 or userY > 19){

        cout << "Enter the Y coordinate (0 - 19)" << endl;

        cin >> userY;
    }

    // checks if the user's inputs matches the balloon's
    if (userX == balX and userY == balY){

        cout << "You found the balloon!" << endl;

        //foundBal is set to true
        foundBal = true;
    }else{
        //function returns false and checkDirection gives a hint of the balloon's location

        cout << "You didn't find the balloon" << endl;

        checkDirection(userX, userY, balX, balY);

        //Adds a "G" to where the user guess the balloon was located at.
        addG(userX,userY,grid);
    }

    return foundBal;
}


/// @brief This function prints out the user's possible choices and validates the user input
/// @return an int ranging from 1-3
int userChoice(){
    int choice = -1;
    
    while (choice < 1 or choice > 3){
        cout << "What would you like to do?" << endl;

        cout << "1. Display Map" << endl;

        cout << "2. Guess Location of Balloon" << endl;

        cout << "3. Exit" << endl;

        cin >> choice;
    }
    
    return choice;
}

/// @brief Takes the user input and returns 
/// @param x user's x coordinate
/// @param y user's y coordinate
/// @param balX balloon's x coordinate
/// @param balY balloon's y coordinate
void checkDirection(int x, int y, int balX, int balY){

    //Checks that the user's x and y are not equal to the balloon's
    if (x != balX or y != balY){
        //if the user's y value is less than the balloon's, prints out that the balloon
        //is further up North
        if (y > balY){

            cout << "The baloon is further North." << endl;

        //if the user's y value is greater than the balloon's, prints out that the balloon
        //is further down South
        }else if(y < balY){

            cout << "The baloon is further South." << endl;

        //Once the user's north/south value is correct, the function looks at the x coordinate
        }else{

            //if the user's x value is less than the balloon's, prints out that the balloon
            //is further West
            if (x > balX){

                cout << "The baloon is further West." << endl;

            //if the user's x value is greater than the balloon's, prints out that the balloon
            //is further East
            }else if (x < balX){

                cout << "The baloon is further East." << endl;

            }
        }
    }
}

/// @brief Asks the user once they find the balloon if they want to continue playing, if yes, resets the map
/// and changes the balloons location
/// @param balX balloon's x coordinate
/// @param balY balloon's y coordinate
/// @param grid the multidimensional array 
/// @return if the user decided to end the game or not
bool countinuePlaying(int balX, int balY, string grid[GRID_Y][GRID_X]){
    char playAgain;
    bool dontEnd = false;


    cout << "Would you like to play again? (y or n)" << endl;
    cin >> playAgain;

    //validates the user's input
    while (!(playAgain == 'y' or playAgain == 'n')){
        cout << "Please type y or n" << endl;

        cin.clear();

        cin.ignore(132, '\n');

        cin >> playAgain;
    }


    if (playAgain == 'y'){

        dontEnd = true;
        
        //reset every value in grid to "$"
        resetGrid(grid);


    }else{
        //if user input is not "y", end the game
        dontEnd = false;

        cout << "Thank you for Using the Surveillance Balloon Tracker" << endl;
    }
    return dontEnd;
}
