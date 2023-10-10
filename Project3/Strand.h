#ifndef STRAND_H
#define STRAND_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
  char m_data;
  Node *m_next;
};

class Strand {
 public:
  // Name: Strand() - Default Constructor
  // Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
  // Preconditions: None
  // Postconditions: Creates a new strand with a default name
  Strand();
  // Name: Strand(string) - Overloaded Constructor
  // Desc: Used to build a new empty strand with the name passed
  //       with m_head, m_tail = nullptr; size = 0;
  // Preconditions: None
  // Postconditions: Creates a new strand with passed name
  Strand(string);
  // Name: ~Strand() - Destructor
  // Desc: Used to destruct a strand
  // Preconditions: There is an existing strand with at least one node
  // Postconditions: Strand is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Strand();
  // Name: InsertEnd
  // Desc: Takes in a char. Creates a new node.
  //       Inserts node at the end of the strand. Increases size.
  // Preconditions: Requires a strand
  // Postconditions: Strand is larger.
  void InsertEnd(char data);
  // Name: GetName()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_name;
  string GetName();
  // Name: GetSize()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_size;
  int GetSize();
  // Name: ReverseSequence
  // Preconditions: Reverses the strand
  // Postconditions: Strand sequence is reversed in place; nothing returned
  void ReverseSequence();
  // Name: GetData
  // Desc: Returns the data at a specific location in the strand.
  //       Iterates to node and returns char.
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns a single char from a node
  char GetData(int nodeNum);
  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from strand
  //       Iterates over the entire strand and builds an output stream
  //       (Called like cout << *m_DNA.at(i); in Sequencer)
  // Preconditions: Requires a strand
  // Postconditions: Returns an output stream (does not cout the output)
  friend ostream &operator<< (ostream &output, Strand &myStrand);
 private:
  string m_name; //Name of the strand
  Node *m_head; //Front of the strand
  Node *m_tail; //End of the strand
  int m_size; //Total size of the strand
};

#endif
