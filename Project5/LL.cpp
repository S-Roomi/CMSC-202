#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node
{
public:
  Node(const T &data);                // Node Constructor - Assume each quan
  pair<T, int> &GetData();            // Node Data Getter
  void SetData(const pair<T, int> &); // Node Data Setter
  Node<T> *GetNext();                 // Node m_next getter
  void SetNext(Node<T> *next);        // Node m_next setter
private:
  pair<T, int> m_data; // Holds templated data
  Node<T> *m_next;     // Pointer to next node
};

template <class T>
Node<T>::Node(const T &data)
{
  m_data = make_pair(data, 1);
  m_next = nullptr;
}

template <class T>
pair<T, int> &Node<T>::GetData()
{
  return m_data;
}

template <class T>
void Node<T>::SetData(const pair<T, int> &data)
{
  m_data = data;
}

template <class T>
Node<T> *Node<T>::GetNext()
{
  return m_next;
}

template <class T>
void Node<T>::SetNext(Node<T> *next)
{
  m_next = next;
}

// Templated Linked List class
template <class T>
class LL
{
public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL &a);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T> &operator=(const LL &);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T> *Find(const T &data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T &);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node.
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T &);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream &operator<<(ostream &output, const LL<U> &);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T, int> &operator[](int x); // Overloaded [] operator to pull data from LL
private:
  Node<T> *m_head; // Node pointer for the head
  int m_size;      // Number of nodes in queue
};

template <class T>
LL<T>::LL()
{
  //set m_head to nullptr and m_size to 0
  m_head = nullptr;
  m_size = 0;
}

template <class T>
LL<T>::~LL()
{
  //curr is used to iterate through the Linked list
  Node<T> *curr = m_head;

  while (curr != nullptr)
  {
    //set m_head to curr, curr to the next value
    //and delete the Node at m_head
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }

  //Everything has been delete and now set 
  //m_head to nullptr and m_size to 0
  m_head = nullptr;
  m_size = 0;
}

template <class T>
LL<T>::LL(const LL &obj)
{
  //use overloaded operator = to set the current LL to the passed LL
  *this = obj;
}

template <class T>
LL<T> &LL<T>::operator=(const LL &newLL)
{
  //curr is the current's LL head
  Node<T> *curr = m_head;

  //newCurr is the passed LL head
  Node<T> *newCurr = newLL.m_head;

  //if there is no LL
  if (m_head == nullptr)
  {
    //iterate through the new LL 
    while (newCurr != nullptr)
    {
      //for each value, insert the data to the current LL
      for (int i = 0; i < newCurr->GetData().second; i++)
      {
        Insert(newCurr->GetData().first);
      }
      //newCurr points the next Node
      newCurr = newCurr->GetNext();
    }
    //return the new LL
    return *this;
  }

  //if the current Linked list is not empty
  while (newCurr->GetNext() != nullptr)
  {
    if (curr->GetNext() != nullptr)
    {
      //change the data in each node
      curr->SetData(newCurr->GetData());
      curr = curr->GetNext();
    }
    else
    {
      //add a new node with the new data
      Insert(newCurr->GetData().first);
    }

    newCurr = newCurr->GetNext();
  }


  Node<T> *prev = m_head;

  //set curr back to m_head
  curr = m_head;

  //check if the current Linked list is greater than the old one
  if (newLL.m_size < m_size)
  {
    //set prev and curr to the latest newLL node
    for (int i = 0; i < newLL.m_size; i++)
    {
      prev = prev->GetNext();
      curr = curr->GetNext();
    }

    //if curr can go futher in the current node, delete those Node
    while (curr != nullptr)
    {
      prev = curr;
      curr = curr->GetNext();
      delete prev;
    }
  }

  //return current LL
  return *this;
}

template <class T>
Node<T> *LL<T>::Find(const T &data)
{
  // create a pointer curr that is equal to m_head
  Node<T> *curr = m_head;

  // iterate through the linked list until we reach the end
  while (curr != nullptr)
  {

    // check the data at the current node
    if (curr->GetData().first == data)
    {

      // returns Node pointer if found
      return curr;
    }

    // move onto the next node
    curr = curr->GetNext();
  }

  // Returns nullptr if not found
  return nullptr;
}

template <class T>
void LL<T>::Insert(const T &data)
{
  //bool to check if the data needs to be place
  //before m_head
  bool beforeHead = false;

  //if the size is 0, add the data the LL
  if (m_size == 0)
  {
    m_head = new Node<T>(data);
    m_size++;
    return;
  }

  // temp curr to iterate through LL
  Node<T> *curr = m_head;
  
  //findData is either a Node or nullptr
  Node<T> *findData = Find(data);

  //if findData has a Node, that means the data is already
  //in the LL so add to the frequency
  if (findData != nullptr)
  {
    findData->GetData().second++;
    return;
  }

  //since we reach this part of the code, we know that we need to add
  //a new node

  //newNode is a new Node with the data passed into it
  Node<T> *newNode = new Node<T>(data);

  //Check if we need to add the data before m_head
  if (data < curr->GetData().first)
  {
    beforeHead = true;
  }
  //else, iterate through the LL and check we need to insert the data in
  //alphabetical order 
  else
  {
    while (curr->GetNext() != nullptr && data > curr->GetNext()->GetData().first)
    {
      curr = curr->GetNext();
    }
  }

  //if beforeHead is true, add the new node and make it point to m_head
  //then set m_head to the new node
  //increase m_size
  if (beforeHead == true)
  {
    newNode->SetNext(m_head);
    m_head = newNode;
    m_size++;
    return;
  }

  //since this code has been reached, that means beforeHead is false
  //so add the newNode and point it to what curr is pointing to.
  //then point curr to the newNode
  newNode->SetNext(curr->GetNext());
  curr->SetNext(newNode);

  //increase size
  m_size++;
}

template <class T>
void LL<T>::RemoveAt(const T &data)
{
  //set curr and prev to m_head
  Node<T> *curr = m_head;
  Node<T> *prev = m_head;

  //set next to what m_head is pointing to
  Node<T> *next = m_head->GetNext();

  //while curr is not nullptr
  while (curr != nullptr)
  {
    //check if the data is at m_head
    if (curr == m_head && curr->GetData().first == data)
    {
      //delete m_head
      delete m_head;

      //set m_head to next
      m_head = next;

      //decrease size
      m_size--;

      return;
    }

    //if the data is equal to curr->GetData().first
    if (curr->GetData().first == data)
    {
      //set point prev to next
      prev->SetNext(next);

      //delete the curr Node
      delete curr;

      //decrease the size
      m_size--;

      return;
    }

    //set prev to curr, curr to next, and next to next->GetNext()
    prev = curr;
    curr = next;
    next = next->GetNext();
  }
}

template <class T>
void LL<T>::Display()
{
  //use overloaded operator <<
  cout << *this << endl;
}

template <class T>
int LL<T>::GetSize()
{
  //return m_size;
  return m_size;
}

template <class U>
ostream &operator<<(ostream &output, const LL<U> &linkList)
{

  // iterate through the linked list and add the value to output
  Node<U> *curr = linkList.m_head;

  while (curr != nullptr)
  {
    //add the data to output
    output << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();
  }

  //return output
  return output;
}

template <class T>
pair<T, int> &LL<T>::operator[](int x)
{
  //set curr to m_head
  Node<T> *curr = m_head;

  //iterate curr to the passed value
  for (int i = 0; i < x; i++)
  {
    curr = curr->GetNext();
  }

  //return curr->GetData()
  return curr->GetData();
}
