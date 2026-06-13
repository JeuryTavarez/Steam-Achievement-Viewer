#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include "Node.h"
#include <string>

class LinkedList {
private:
    Node* head_ptr_;   
    int item_count_;    

public:
    LinkedList();
    virtual ~LinkedList(); 

    bool isEmpty() const;
    int getLength() const;

    bool insert(int new_position, const std::string& new_entry);
    void clear();

    Node* getNodeAt(int position) const;
};

#endif