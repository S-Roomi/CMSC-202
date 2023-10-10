#ifndef BLOON_H_
#define BLOON_H_
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Parent class for all factions
class Bloon {
 public:
  // Name: Bloon() - Default Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes (may not be specifically used)
  Bloon();
  // Name: Bloon(int health, int location) - Overloaded Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes
  Bloon(int health, int location);
  // Name: virtual ~Bloon - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  virtual ~Bloon();
  // Name: GetHealth()
  // Description: Returns health of bloon
  // Preconditions: Bloon has health
  // Postconditions: None
  int GetHealth();
  // Name: SetHealth()
  // Description: Sets health of bloon
  // Preconditions: None
  // Postconditions: Health is set
  void SetHealth(int);
  // Name: GetLocation()
  // Description: Returns location of bloon
  // Preconditions: Bloon has location
  // Postconditions: None
  int GetLocation();
  // Name: SetLocation()
  // Description: Sets location of bloon
  // Preconditions: None
  // Postconditions: Location is set
  void SetLocation(int);
  // Name: Pop()
  // Description: Defines popping
  // Preconditions: None
  // Postconditions: None (Purely virtual - must be in child classes)
  virtual int Pop(int damage) = 0;
  // Name: GetColor
  // Description: Virtual
  // Preconditions: None
  // Postconditions: None (Purely virtual - must be in child classes)
  virtual string GetColor() = 0;
  // Name: Overloaded <<
  // Description: Prints the details of an bloon
  // Preconditions: all variables are set valid
  // Postconditions: returns an ostream with output of bloon
  friend ostream& operator<<(ostream&, Bloon&);
private:
  int m_health; //Health of bloon
  int m_location; //Location of bloon on track
};

#endif
