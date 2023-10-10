#include "Game.h"
/*************************************************************** 
** File: Game.cpp
** Description: This file contains the Game class function definitions
***************************************************************/



/*
Shop m_myShop; //Player's Shop for the game
Ingredient m_ingredients[PROJ2_SIZE]; //All ingredients in the game (loaded from file)
*/

//Constructor
Game::Game(){
    //Create a string to store the player's name
    string playerName;

    //Ask the player for the name of their shop.
    cout << "What is the name of your Shop?" << endl;

    //get the player's name and put it in playerName
    getline(cin,playerName);

    //Set the shop's name as the name the player inputed
    m_myShop.SetName(playerName);


}


void Game::LoadIngredients(){
    
    /*
    arr[100] goal is to store the information that was retrieved from the file of
    ingredients
    */
    string arr[100];


    //index is used to make adding information to arr easier
    int index = 0;

    /*
    a placeholder string that will store the information retrieved from the file
    of ingredients to be then transfered over to arr
    */
    string fileInfo;


    /*
    These two lines of code first store fstream as the name file and then open
    the file name stored in PROJ2_DATA in read mode.
    */
    fstream file;
    file.open(PROJ2_DATA, ios::in); 

    /*
    This while loop gets each line in the opened file and puts all the information
    into the array arr. 
    This is also where I used index
    */
    while(getline(file, fileInfo, '\n')){
        arr[index] = fileInfo;

        index++;
    }
    
    //Once everything has been added to arr, the file closes
    file.close();




    /*
    Since this part of the function has a different purpose (the top was to get info and below is to read/alter the data), 
    I assigned the variables I needed over here just for organization sake.
    */

    /*
    spaceDifference takes three different integers which represent the space
    between each comma
    */
    int spaceDifference[3];

    /*
    spaces will be used to measure the spaces between commas 
    */
    int spaces = 0;

    /*
    spaceDifIndex is used to add elements into spaceDifference
    */
    int spaceDifIndex = 0;

    
    //ingredientIndex is used when adding variables to m_ingredients
    int ingredientIndex = 0;
    

    /*
    this loop finds the commas in each sentence retrieved from the project file and
    adds it to m_ingredients and calls AddIngredient.
    */
    for (int i = 0; i < PROJ2_SIZE; i++){

        //strLength is the length of the string from arr
        int strLength = arr[i].length();
        
        /*
        This for loop loops through each character in a string and finds
        the position of each comma in said string
        */
        for (int j = 0 ; j < strLength; j++){
            
            /*
            if statement checks if the character is not a comma and increase
            spaces by one if its not

            if the character is a comma, it adds the variable spaces to spaceDifference 
            */
            if (arr[i][j] != ','){
                
                spaces++;
            
            }else{
                
                spaceDifference[spaceDifIndex] = spaces;

                spaceDifIndex++;
            }
        }

        //resets spaces and spaceDifIndex back to zero for the next loop
        spaces = 0;
        spaceDifIndex = 0;

        /*
        a temporary Ingredient named temp just to store information and put it
        in m_ingredients and AddIngredient
        */
        Ingredient temp;

        /*
        The code bellow takes the difference between commas and creates a sub-string
        with that information. The first one is the name, the second is the type,
        the third and fourth are the ingredients
        */


        //0-first comma
        temp.m_name = arr[i].substr(0,spaceDifference[0]);

        //first comma <---> second comma
        temp.m_type = arr[i].substr(spaceDifference[0]+1, (spaceDifference[1]-1)-(spaceDifference[0]-1));
    
        //second comma <--> third comma
        temp.m_ingredient1 = arr[i].substr(spaceDifference[1]+2, spaceDifference[2] - spaceDifference[1]);

        //third comma <--> end
        temp.m_ingredient2 = arr[i].substr(spaceDifference[2]+3);

        //set quantity to zero instead of undefined
        temp.m_quantity = 0;


        //adds the temp Ingredient to the arrays and increases ingredientIndex

        m_ingredients[ingredientIndex] = temp;

        m_myShop.AddIngredient(temp);

        ingredientIndex++;
    }

    //Once everything is done, this cout message is printed
    cout << "32 ingredients loaded." << endl;
}

void Game::StartGame(){
    //Calls GameTitle() and LoadIngredients() immediately as the game starts
    GameTitle();
    LoadIngredients();

    
    bool gameOver = false;


    int userChoice;

    /*
    While the game isn't over, this while loop constantly runs MainMenu()
    and uses a switch statement to check the user's choice and determine 
    what to do
    */
    while (gameOver == false){
        userChoice = MainMenu();
        switch (userChoice){
            case 1:
                DisplayIngredients();
                break;
            case 2:
                SearchIngredients();
                break;
            case 3:
                CombineIngredients();
                break;
            case 4:
                m_myShop.ShopScore();
                break;
            case 5:
                gameOver = true;
                break;
        }
    }
}

void Game::DisplayIngredients(){
    /*
    This for loop loops through each ingredient in the user's shop and
    displays the name of the ingredient and its quantity.
    */
    for (int i = 0; i < PROJ2_SIZE; i++){

        //A temporary variable to store the information from GetIngredient()
        Ingredient temp = m_myShop.GetIngredient(i);

        cout << i+1 << ". " << temp.m_name << " " << temp.m_quantity << endl;
       
    }
}

int Game::MainMenu(){
    /*
    What would you like to do in JD's shop?
    1. Display your Shop's Ingredients
    2. Search for Natural Ingredients
    3. Attempt to Merge Ingredients
    4. See Score
    5. Quit
    */

    //userChoice stores the int that represents the user's action
    int userChoice;


    //asks the user what they like to do (They type a number between 1-5)
    cout << "What would you like to do in " << m_myShop.GetName() << "'s shop?" << endl;
    cout << "1. Display your Shop's Ingredients" << endl;
    cout << "2. Search for Natural Ingredients" << endl;
    cout << "3. Attempt to Merge Ingredients" <<endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;

    //store user input in userChoice
    cin >> userChoice;
    

    //checks to see if userChoice is between 1-5
    while (userChoice < 1 || userChoice > 5){
        
        //the user's choice was invalid, ask them to pick again
        cout << "Please enter a number between 1-5" << endl;
        cin.ignore(120,'\n');
        cin >> userChoice;
    }

    return userChoice;
}


void Game::SearchIngredients(){

    //stores the number of natural ingredients
    int numOfNatural = 0;

    /*
    This for loop checks all the ingredients and finds the number of natural
    ingredients and stores that number in numOfNatural
    */
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_ingredients[i].m_type == "natural"){
            numOfNatural++;
        }
    }

    //create a array, natural that stores all the natural ingredients
    Ingredient natural[numOfNatural];

    //index is for adding things into natural
    int index = 0;


    //adds all natural ingredients to natural
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_ingredients[i].m_type == "natural"){
            natural[index] = m_ingredients[i];
            index++;
        }
    }

    //random gets a random value from 0-9
    int random = rand() % 10;

    /*
    randomIngredient just stores the random ingredient from the list
    of natural ingredients

    This is not needed but just makes the code look a little better/cleaner
    */
    Ingredient randomIngredient = natural[random];

    
    //Increase the random ingredient's quantity
    m_myShop.IncrementQuantity(randomIngredient);

    //tells the user what ingredient they found
    cout << randomIngredient.m_name << " Found!" << endl;
    
}

void Game::CombineIngredients(){
    //x and y represent the first and second ingredient the user selects
    int x,y = -10;

    //ask the user the first ingredient to merge
    cout << "Which ingredients would you like to merge? (Enter the number to the left of Ingredient)" << endl;
    cout << "To list known ingredients enter -1" << endl;
    cin >> x;
    
    //Calls RequestIngredient to validate/alter the user's choice 
    RequestIngredient(x);

    //After RequestIngredient altered the value, if it was incorrect, ask the user
    //for input again
    while (x < 0 || x > 31){
        cin >> x;
        RequestIngredient(x);
    }
    

    //Asks the user for the second ingredient
    cout << "Which ingredients would you like to merge? (Enter the number to the left of Ingredient)" << endl;
    cout << "To list known ingredients enter -1" << endl;

    //Ignores/cleans the consle
    cin.ignore(120,'\n');


    //stores the new value in y
    cin >> y;

    //Calls RequestIngredient to validate/alter the user's choice 
    RequestIngredient(y);

    //After RequestIngredient altered the value, if it was incorrect, ask the user
    //for input again
    while (y < 0 || y > 31){

        cin >> y;

        RequestIngredient(y);
    }
    

    //Create a new valiable z for the product of the two ingredients if it exists
    int z;


    //Create two temp variables to store the information from GetIngredient
    Ingredient firstIngredient, secondIngredient;

    firstIngredient = m_myShop.GetIngredient(x);
    secondIngredient = m_myShop.GetIngredient(y);


    //z equals the product/recipe of the two provided ingredients
    z = SearchRecipes(firstIngredient.m_name,secondIngredient.m_name);

    //Create two booleans to check which if statement was ran
    bool firstIf = false;
    bool secondIf = false;

    //makes a variable to use CheckQuantity to check the quantity of firstIngredient and secondIngredient
    bool checkIngredient = m_myShop.CheckQuantity(firstIngredient,secondIngredient);

    //Checks if the name of the two ingredients are not equal and if both the quantities are greater than 0
    if ((firstIngredient.m_name != secondIngredient.m_name) && (checkIngredient == true)){
        //if z equals negative one, that means that the recipe does not exist
        //and the combination does not work
        if (z == -1){

            cout << "This combination does not work" << endl;

        }else{
            /*
            if the combination exists, increase the product (z)
            and decrease firstIngredient and secondIngredient
            */
            m_myShop.IncrementQuantity(m_myShop.GetIngredient(z));

            m_myShop.DecrementQuantity(firstIngredient);

            m_myShop.DecrementQuantity(secondIngredient);


            //Tells the user what they made
            cout << "Made " << m_myShop.GetIngredient(z).m_name << endl;
        }

        //Since this if statement was ran, set firstIf to true
        firstIf = true;

    //this if statement checks if the two provide ingredients are the same and if they are
    //the quantity of said ingredient needs to be greater than 1
    }else if ((firstIngredient.m_name == secondIngredient.m_name) && (firstIngredient.m_quantity > 1)){

        //if z equals negative one, that means that the recipe does not exist
        //and the combination does not work
        if (z == -1){

            cout << "This combination does not work" << endl;


            /*
            if the combination exists, increase the product (z)
            and decrease firstIngredient and secondIngredient
            */
        }else{
            
            m_myShop.IncrementQuantity(m_myShop.GetIngredient(z));

            m_myShop.DecrementQuantity(firstIngredient);

            m_myShop.DecrementQuantity(secondIngredient);

            //Tells the user what they made
            cout << "Made " << m_myShop.GetIngredient(z).m_name << endl;
        }

        //Since this if statement was ran, set secondIf to true
        secondIf = true;
    }else{

        //these two if statements run if and only the first if statement was ran 

        //checks if the user didn't have enough of the first ingredient
        if (firstIf == true && firstIngredient.m_quantity == 0){

            cout << "You don't have enough of " << firstIngredient.m_name << endl;
        }

        //checks if the user didn't have enough of the second ingredient
        if (firstIf == true && secondIngredient.m_quantity == 0){
            cout << "You don't have enough of " << secondIngredient.m_name << endl;
        }

        //Only happens if second if statement was ran.

        //Checks to see if the user didn't have enough of the first ingredient
        if (secondIf == true && firstIngredient.m_quantity < 2){

            cout << "You don't have enough of " << firstIngredient.m_name << endl;

        //Checks to see if the user didn't have enough of the second ingredient
        }else if ((firstIngredient.m_name == secondIngredient.m_name) && firstIngredient.m_quantity < 2){
            cout << "You don't have enough of " << firstIngredient.m_name << endl;
        }

        //if both the statements don't run, that means the quantity isn't enough
        if (firstIf == false and secondIf == false){
            cout << "You don't have enough of " << firstIngredient.m_name << endl;
            cout << "You don't have enough of " << secondIngredient.m_name << endl;
        }
    }
}

void Game::RequestIngredient(int &choice){
    //Takes a int and checks if is equal to -1
    if (choice == -1){

        // if choice == -1, then display the list
        DisplayIngredients();

    //else if choice was between 1-32, subtract one so it works if
    //we input it into an array    
    }else if (choice >= 1 && choice <= 32){

        choice -= 1;

    //if both the previous if statements didn't run, that means choice is a invalid
    //number 
    }else{

        cout << "Enter a number between 1-32 or -1 for list of Ingredients" << endl;
    }

}

int Game::SearchRecipes(string item1, string item2){

    //loops through each element in m_ingredient
    for (int i = 0; i < PROJ2_SIZE; i++){

        //These two bools check to see if the ingredient is
        //located in another ingredient
        bool firstCheck = false;
        bool secondCheck = false;


        //if the first or second ingredient equals to item1, set first check to true
        if (m_ingredients[i].m_ingredient1 == item1 || m_ingredients[i].m_ingredient2 == item1){
            
            firstCheck = true;
        }


        //if the first or second ingredient equals to item2, set second check to true
        if (m_ingredients[i].m_ingredient2 == item2 || m_ingredients[i].m_ingredient2 == item2){
            
            secondCheck = true;
        }

        //if both checks equal true, that means that the ingredient found has ingredient1 and ingredient2
        //equal to item1 and item2
        //return the index of that ingredient
        if (firstCheck == true && secondCheck == true){

            return i;
        }

    }

    //else if there is no ingredient that has both item 1 and 2 in it, return -1
    return -1;
}