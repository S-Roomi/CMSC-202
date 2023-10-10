#include "Monkey.h"

Monkey::Monkey(){
    //Set m_type to None, m_damage and location to 0
    m_type = "None";
    m_damage = 0;
    m_location = 0;
}

Monkey::Monkey(string type, int damage, int location){
    //set m_type, m_damage, and m_location to the value passed
    m_type = type;
    m_damage = damage;
    m_location = location;
}

Monkey::~Monkey(){
    //emtpy m_type, set m_damage. and m_location to 0
    m_type.clear();
    m_damage = 0;
    m_location = 0;
}

int Monkey::GetDamage(){
    //Getter for m_damage
    return m_damage;
}

string Monkey::GetType(){
    //getter for m_type
    return m_type;
}

int Monkey::GetLocation(){
    //Getter for m_location
    return m_location;
}

void Monkey::SetDamage(int damage){
    //setter for m_damage
    m_damage = damage;
}

void Monkey::SetType(string type){
    //setter for m_type
    m_type = type;
}

void Monkey::SetLocation(int location){
    //setter for m_location
    m_location = location;
}

ostream& operator<<(ostream& output, Monkey& myMonkey){
    //adds to ostream all of the monkey's information and returns ostream
    output << myMonkey.m_type << ": " 
    << "Location: " << myMonkey.m_location + 1 << " Damage: " << myMonkey.m_damage;
    return output;
}