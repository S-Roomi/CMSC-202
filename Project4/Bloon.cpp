#include "Bloon.h"

Bloon::Bloon(){
    //set Bloon health to zero and position to -1
    m_health = 0;
    m_location = -1;
}

Bloon::Bloon(int health, int location){
    //set m_health and location to health and location
    m_health = health;
    m_location = location;
}

Bloon::~Bloon(){
    //set m_health and m_location to 0
    m_health = 0;
    m_location = 0;
}

int Bloon::GetHealth(){
    //get for m_health
    return m_health;
}

void Bloon::SetHealth(int health){
    //setter for m_health
    m_health = health;
}

void Bloon::SetLocation(int location){
    //setter for m_location
    m_location = location;
}

int Bloon::GetLocation(){
    //getter for m_location 
    return m_location;
}

ostream& operator<<(ostream& output, Bloon& myBloon){
    //add to ostream the bloon's information and return the ostream
    
    output << "Bloon: " << myBloon.GetColor() << " Health: " << myBloon.m_health;
    return output;
}