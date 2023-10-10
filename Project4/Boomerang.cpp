#include "Boomerang.h"

//use Monkey default Constructor
Boomerang::Boomerang():Monkey(){}

//use Monkey overloaded Constructor
Boomerang::Boomerang(string type, int damage, int location)
:Monkey(type,damage,location){}

//use Monkey's virtual deconstuctor
Boomerang::~Boomerang(){}

int Boomerang::Attack(vector<Bloon*> bloon){
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
            cout << "The boomerang monkey throws a boomerang!" << endl;
            cout << "The " << myBloon->GetColor() <<" bloon pops!" << endl;
            totalPops += myBloon->Pop(monkeyDamage);
            
            if (myBloon->GetHealth() > 0){
                cout << "The " << myBloon->GetColor() <<" bloon pops!" << endl;
                totalPops += myBloon->Pop(monkeyDamage);
            }
            
        }

       
    }
    //return totalPops
    return totalPops;
}