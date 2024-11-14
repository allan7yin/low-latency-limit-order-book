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

    void Insert(DoublyLinkedListNode<T> *node);
    // DoublyLinkedListNode<T> *Search(T value);
    bool Delete(DoublyLinkedListNode<T> *node);
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
void DoublyLinkedList<T>::Insert(DoublyLinkedListNode<T> *node) {
    if (end == nullptr) {
        start = end = node;
    } else {
        end->next = node;
        node->prev = end;
        end = node;
    }
    size++;
}

// template <class T>
// DoublyLinkedListNode<T> *DoublyLinkedList<T>::Search(T value) {
//     DoublyLinkedListNode<T> *current = start;
//     while (current) {
//         if (current->value == value) {
//             return current;
//         }
//         current = current->next;
//     }
//     return nullptr;
// }

template <class T>
bool DoublyLinkedList<T>::Delete(DoublyLinkedListNode<T> *node) {
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