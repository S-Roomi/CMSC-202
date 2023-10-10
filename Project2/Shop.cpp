#include "Shop.h"

/*************************************************************** 
** File: Shop.cpp
** Description: This file contains the Shop class function definitions
***************************************************************/

Shop::Shop(){
    //Sets all the member variables to a preset

    m_shopName = "test";

    m_numIngredients = 0;

    m_shopRank = 'F';
}


Shop::Shop(string name){
    //Sets all the member variables to a preset

    m_shopName = name;

    m_numIngredients = 0;

    m_shopRank = 'F';
}


string Shop::GetName(){

    //getter function for getting m_shopName

    return m_shopName;
}


void Shop::SetName(string name){
    
    //setter function for setter the shopName

    m_shopName = name;
}


int Shop::CheckIngredient(Ingredient ingredient){
    //Loops through each ingredient and checks if ingredient is equal to 
    //a ingredient in m_myIngredient
    for(int i = 0; i < PROJ2_SIZE; i++){

        if (m_myIngredients[i].m_name == ingredient.m_name && 

            m_myIngredients[i].m_type == ingredient.m_type &&

            m_myIngredients[i].m_ingredient1 == ingredient.m_ingredient1 &&

            m_myIngredients[i].m_ingredient2 == ingredient.m_ingredient2){

            //If they are equal, return the index of that ingredient
            return i;
        }
    }

    //if no ingredient is equal to the passed ingredient, return -1
    return -1;
}


void Shop::AddIngredient(Ingredient ingredient){

    //sets the passed ingredient quantity to zero
    ingredient.m_quantity = 0;

    //adds all the passed ingredient to m_myIngredients
    m_myIngredients[m_numIngredients] = ingredient;

    //increase the m_numIngredients
    m_numIngredients += 1;
}


void Shop::IncrementQuantity(Ingredient ingredient){
    //Checks if the ingredient exists in m_myIngredient
    int index = CheckIngredient(ingredient);

    //if the ingredient exists, increase the quantity, else do nothing if it doesn't
    //exist
    if (index != -1){

        m_myIngredients[index].m_quantity += 1;

    }
}


bool Shop::DecrementQuantity(Ingredient ingredient){
    ////Checks if the ingredient exists in m_myIngredient
    int index = CheckIngredient(ingredient);

    //if the ingredient exists and the quantity is not zero,
    //decrease the quantity by one and return true, else return false
    if (index != -1){
        if (m_myIngredients[index].m_quantity != 0){
            m_myIngredients[index].m_quantity -= 1;
            return true;
        }
        return false;
    }
    return false;
}


bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2){
    bool firstIngredient = false;
    bool secondIngredient = false;
    
    //checks if the first ingredient quantity is greater than 0
    //if so, firstIngredient == true
    if(ingredient1.m_quantity > 0){

        firstIngredient = true;

    }

    ////checks if the second ingredient quantity is greater than 0
    //if so, secondIngredient == true
    if(ingredient2.m_quantity > 0){

        secondIngredient = true;

    }

    //if both firstIngredient and secondIngredient == true, return true
    if(firstIngredient == true && secondIngredient == true){

        return true;
    }

    return false;
}


Ingredient Shop::GetIngredient(int x){
    //Getter function to get the ingredient at the int
    //passed

    return m_myIngredients[x];
}


int Shop::IngredientCount(){
    //set countOfIngredients to zero
    int countOfIngredients = 0;

    //loop through each ingredient in m_myIngredients and see if the ingredient
    //quantity is greater than zero. If it is, increase countOfIngredients
    for (int i = 0; i < PROJ2_SIZE; i++){

        if (m_myIngredients[i].m_quantity > 0){

            countOfIngredients += 1;

        }
    }

    //return countOfIngredients once the loop finishes
    return countOfIngredients;
}


void Shop::CalcRank(){
    //set count to the number of Ingredients
    double count = IngredientCount();

    //set percent to the count divided by the project size
    //it also multiplies the total by 100 to make it a percentage
    double percent = (count/PROJ2_SIZE)*100;
    
    //if statement checks the percent and determines what rank 
    //it will be because of it.
    if (percent <= 29){
        m_shopRank = 'F';
    }else if (percent > 29 && percent <= 49){
        m_shopRank = 'D';
    }else if (percent > 49 && percent <= 69){
        m_shopRank = 'C';
    }else if (percent > 69 && percent <= 89){
        m_shopRank = 'B';
    }else if (percent > 89 && percent <= 99){
        m_shopRank = 'A';
    }else{
        m_shopRank = 'S';
    }

}


char Shop::GetRank(){
    //getter function for m_shopRank
    return m_shopRank;
}


void Shop::ShopScore(){
    //ingredientFound to the ingredient count
    double ingredientFound = IngredientCount();

    //set percent to the count divided by the project size
    //it also multiplies the total by 100 to make it a percentage
    double percentage = (ingredientFound/PROJ2_SIZE)*100;

    //calculate the current rank of the shop and set it to rank
    CalcRank();
    char rank = GetRank();


    //Displays all the shop's information and its score
    cout << "***The Potion Shop***" << endl;
    cout << "Owned by: " << GetName() << endl;
    cout << "There are " << PROJ2_SIZE << " available products." << endl;
    cout << "This shop has " << ingredientFound << " products in stock." << endl;
    cout << "Which is " << percentage << "%" << endl;
    cout << "Shop Rank: " << rank << endl;

    //if the shop's rank is equal to 'S', print to the user that they won the game.
    if (rank == 'S'){
        cout << "You have achieved greatness. You've Won the Game" << endl;
    }
    cout << "*********************" << endl;

}