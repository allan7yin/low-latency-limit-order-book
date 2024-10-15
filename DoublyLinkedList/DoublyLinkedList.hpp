#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include "DoublyLinkedListNode.hpp"

template <class T>
class DoublyLinkedList {
  private:
    DoublyLinkedListNode<T> *start;
    DoublyLinkedListNode<T> *end;
    int size;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedListNode<T> *getStart() const;
    DoublyLinkedListNode<T> *getEnd() const;
    int getSize() const;
    DoublyLinkedListNode<T> *getHeadNode() const;
    DoublyLinkedListNode<T> *getTailNode() const;

    void Insert(T value);
    DoublyLinkedListNode<T> *Search(T value);
    bool Delete(T value);
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : start(nullptr), end(nullptr), size(0) {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (start != nullptr) {
        DoublyLinkedListNode<T> *temp = start;
        start = start->next;
        delete temp;
    }
}

template <class T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::getStart() const {
    return this->start;
}

template <class T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::getEnd() const {
    return this->end;
}

template <class T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template <class T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::getHeadNode() const {
    return this->start;
}

template <class T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::getTailNode() const {
    return this->end;
}

template <class T>
void DoublyLinkedList<T>::Insert(T value) {
    DoublyLinkedListNode<T> *newNode = new DoublyLinkedListNode<T>(value);
    if (end == nullptr) {
        start = end = newNode;
    } else {
        end->next = newNode;
        newNode->prev = end;
        end = newNode;
    }
    size++;
}

template <class T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::Search(T value) {
    DoublyLinkedListNode<T> *current = start;
    while (current) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
bool DoublyLinkedList<T>::Delete(T value) {
    DoublyLinkedListNode<T> *node = Search(value);
    if (!node) return false;

    if (node->next && node->prev) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else if (node->next) {
        start = node->next;
        start->prev = nullptr;
    } else if (node->prev) {
        end = node->prev;
        end->next = nullptr;
    } else {
        start = end = nullptr;
    }

    delete node;
    size--;
    return true;
}
#endif