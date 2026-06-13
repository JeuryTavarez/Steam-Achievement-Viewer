#include "Node.h"

// Default Constructor
Node::Node() : next_(nullptr) {
    
}

// Parameterized Constructor (Data only)
Node::Node(const std::string& an_item) : item_(an_item), next_(nullptr) {
}

// Parameterized Constructor (Data and Next Pointer)
Node::Node(const std::string& an_item, Node* next_node_ptr) : item_(an_item), next_(next_node_ptr) {
}

// Setters
void Node::setItem(const std::string& an_item) {
    item_ = an_item;
}

void Node::setNext(Node* next_node_ptr) {
    next_ = next_node_ptr;
}

// Getters
std::string Node::getItem() const {
    return item_;
}

Node* Node::getNext() const {
    return next_;
}