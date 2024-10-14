#ifndef limit_hpp
#define limit_hpp

#include "../DoublyLinkedList/DoublyLinkedList.hpp"
#include "Order.hpp"

class Limit {
  private:
    int limitPrice;
    int size;
    int totalVolume;
    DoublyLinkedList<Order *> *orders;

  public:
    Limit(int limitPrice, int size, int totalVolume);
    ~Limit();
    Order *getHeadOrder() const;
    int getLimitPrice() const;
    int getSize() const;
    int getTotalVolume() const;

    void addOrder(Order *order);
    void partiallyFillVolume(int orderShares);

    void printForward() const;
    void printBackward() const;
    friend std::ostream &operator<<(std::ostream &os, const Limit &limit);
};

#endif