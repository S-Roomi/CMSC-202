#include "Strand.h"

Strand::Strand() {
    // Set m_head, m_tail to nullptr and m_size to 0
    m_head = nullptr;

    m_tail = nullptr;

    m_size = 0;
}

Strand::Strand(string name) {
    // Set m_head, m_tail to nullptr and m_size to 0 and name to the passed
    // value
    m_name = name;

    m_head = nullptr;

    m_tail = nullptr;

    m_size = 0;
}

Strand::~Strand() {
    // temporary Node
    Node *curr = m_head;

    // iterate through the linked list and deallocate each node
    while (curr != nullptr) {
        m_head = curr;
        curr = curr->m_next;
        delete m_head;
    }

    // Set member variables back to default value
    m_name.clear();
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

void Strand::InsertEnd(char data) {
    // Create a new node
    Node *newNode = new Node();

    // add data to the new node
    newNode->m_data = data;

    // if this is the first node, add it the first position
    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;

        // if not the first node, add it to the end of the linked list
    } else {
        m_tail->m_next = newNode;
        m_tail = newNode;
    }

    // increase m_size
    m_size++;
}

string Strand::GetName() {
    // Getter function for m_name
    return m_name;
}

int Strand::GetSize() {
    // Getter function for m_size
    return m_size;
}

void Strand::ReverseSequence() {
    // if the strand doesn't have any value return nothing and stop the rest of
    // the code from happening
    if (m_head == nullptr) {
        return;
    }

    // same thing as above, can't reverse a single character
    if (m_head->m_next == nullptr) {
        return;
    }

    // Create prev and curr and set them to m_head
    Node *prev = m_head;
    Node *curr = m_head;

    // next is equal to where m_head is pointing to
    Node *next = m_head->m_next;

    curr->m_next = nullptr;

    // while next is not at the end of the linked list
    while (next != nullptr) {
        // set curr to next
        curr = next;

        // set next to the next value
        next = next->m_next;

        // curr points to prev
        curr->m_next = prev;

        // prev then is equal to curr
        prev = curr;
    }
    // point m_head to curr since curr now the first value
    m_head = curr;
}

char Strand::GetData(int nodeNum) {
    // if the value passed is greater than or equal to the size of the strand
    // return '?'
    if (nodeNum >= m_size) {
        return '?';
    } else {
        // create a pointer curr that is equal to m_head
        Node *curr = m_head;

        // iterate through the linked list until we get to the value requested
        for (int i = 0; i < nodeNum; i++) {
            curr = curr->m_next;
        }
        // return the data
        return curr->m_data;
    }
}

ostream &operator<<(ostream &output, Strand &myStrand) {
    // add to output the strand's name
    output << "***" << myStrand.m_name << "***" << endl;

    // iterate through the linked list and add the value to output
    for (int i = 0; i < myStrand.m_size; i++) {
        output << myStrand.GetData(i) << "->";
    }

    // add end at the end of the strand
    output << "END" << endl;

    // return the output
    return output;
}
