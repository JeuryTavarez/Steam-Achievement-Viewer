#include "LinkedList.h"

LinkedList::LinkedList() : head_ptr_(nullptr), item_count_(0) {
}

LinkedList::~LinkedList() {
    clear();
}

bool LinkedList::isEmpty() const {
    return item_count_ == 0;
}

int LinkedList::getLength() const {
    return item_count_;
}

Node* LinkedList::getNodeAt(int position) const {
    Node* curPtr = head_ptr_;
    for (int skip = 1; skip < position; skip++) {
        curPtr = curPtr->getNext();
    }
    return curPtr;
}

bool LinkedList::insert(int new_position, const std::string& new_entry) {
    bool ableToInsert = (new_position >= 1) && (new_position <= item_count_ + 1);
    if (ableToInsert) {
        Node* newNode = new Node(new_entry);
        if (new_position == 1) {
            newNode->setNext(head_ptr_);
            head_ptr_ = newNode;
        }
        else {
            Node* prev = getNodeAt(new_position - 1);
            newNode->setNext(prev->getNext());
            prev->setNext(newNode);
        }
        item_count_++;
    }
    return ableToInsert;
}

void LinkedList::clear() {
    while (!isEmpty()) {
        Node* nodeToDeletePtr = head_ptr_;
        head_ptr_ = head_ptr_->getNext();
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        item_count_--;
    }
}