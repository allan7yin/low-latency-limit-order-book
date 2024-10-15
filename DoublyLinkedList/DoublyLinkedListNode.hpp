#ifndef DoublyLinkedListNode_hpp
#define DoublyLinkedListNode_hpp

template <class T>
struct DoublyLinkedListNode {
  public:
    T value;

    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
    void remove();
    DoublyLinkedListNode(T value, DoublyLinkedListNode *prev = nullptr, DoublyLinkedListNode *next = nullptr);
    ~DoublyLinkedListNode();
};

template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode(T value, DoublyLinkedListNode *prev, DoublyLinkedListNode *next)
    : value(value), next(next), prev(prev) {}

template <class T>
DoublyLinkedListNode<T>::~DoublyLinkedListNode() {
    delete value; // since value is *Order
}

template <class T>
void DoublyLinkedListNode<T>::remove() {
    if (prev != nullptr) {
        prev->next = next;
    }
    if (next != nullptr) {
        next->prev = prev;
    }
    next = nullptr;
    prev = nullptr;
}

#endif