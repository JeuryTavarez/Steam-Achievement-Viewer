#pragma once
#ifndef NODE_HPP_
#define NODE_HPP_
#include <string>

class Node {
private:
    std::string item_;     
    Node* next_;         

public:
    Node();
    Node(const std::string& an_item);
    Node(const std::string& an_item, Node* next_node_ptr);

    void setItem(const std::string& an_item);
    void setNext(Node* next_node_ptr);

    std::string getItem() const;
    Node* getNext() const;
};

#endif