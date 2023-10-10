#include "Dart.h"
#include "Basic.h"

//use Monkey default Constructor
Dart::Dart() : Monkey(){} 

//use Monkey overloaded Constructor
Dart::Dart(string type, int damage, int location) 
: Monkey(type,damage,location){
    // cout << type << endl;
    // cout << damage << endl;
    // cout << location << endl;
}

//use Monkey's virtual deconstuctor
Dart::~Dart(){}


int Dart::Attack(vector<Bloon*> bloon){
    //Set Bloon iterator to ptr
    vector<Bloon*>::iterator ptr;

    //monkey's current location
    int monkeyLocation = GetLocation();
    
    //total amount of pops
    int totalPops = 0;

    //iterator through each bloon in the vector passed
    //for each loop
    for (ptr = bloon.begin(); ptr < bloon.end(); ptr++){

        //set myBloon to ptr
        Bloon *myBloon = *ptr;
        
        //bloonLocation is the bloon's current location
        int bloonLocation = myBloon->GetLocation();

        //the monkey's damage
        int monkeyDamage = GetDamage();

        //if the bloon's location and monkey's are the same
        //attack the bloon and tell that to the user
        if (bloonLocation == monkeyLocation){
            cout << "The Dart monkey throws a dart!" << endl;
            totalPops = myBloon->Pop(monkeyDamage);
            cout << "The " << myBloon->GetColor() <<" bloon pops!" << endl;
        }
    }
    //return totalPops
    return totalPops;
}