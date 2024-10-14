#ifndef DoublyLinkedListNode_hpp
#define DoublyLinkedListNode_hpp

template <class T>
class DoublyLinkedListNode {
  public:
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
    T value;
    DoublyLinkedListNode(T value, DoublyLinkedListNode *prev = nullptr, DoublyLinkedListNode *next = nullptr) : value(value), prev(prev), next(next) {}
};

#endif