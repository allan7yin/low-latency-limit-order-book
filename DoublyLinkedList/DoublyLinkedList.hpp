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
    DoublyLinkedList() : start(nullptr), end(nullptr), size(0) {}
    ~DoublyLinkedList() {
        while (start != nullptr) {
            DoublyLinkedListNode<T> *temp = start;
            start = start->next;
            delete temp;
        }
    }

    DoublyLinkedListNode<T> *getStart() {
        return this->start;
    }

    DoublyLinkedListNode<T> *getEnd() {
        return this->end;
    }

    void Insert(T value) {
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

    DoublyLinkedListNode<T> *Search(T value) {
        DoublyLinkedListNode<T> *current = start;
        while (current) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool Delete(T value) {
        DoublyLinkedListNode<T> *node = search(value);
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
        return true;
    }

    int getSize() const {
        return size;
    }
};

#endif