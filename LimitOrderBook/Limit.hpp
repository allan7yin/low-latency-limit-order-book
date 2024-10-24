#ifndef limit_hpp
#define limit_hpp

#include "DoublyLinkedList/DoublyLinkedList.hpp"
#include "Order.hpp"
#include <iostream>

class Order;

class Limit {
  private:
    int limitPrice;
    bool buyOrSell;
    int size;
    int totalVolume;

    DoublyLinkedList<Order *> *orders;

  public:
    Limit(int limitPrice, bool buyOrSell, int size = 0, int totalVolume = 0);
    ~Limit();
    Order *getHeadOrder();
    int getLimitPrice() const;
    int getSize() const;
    int getTotalVolume() const;
    bool getBuyOrSell() const;
    DoublyLinkedList<Order *> *getOrders() const;

    void addOrder(Order *order);
    void partiallyFillVolume(int orderShares);

    void printForward() const;
    void printBackward() const;
    friend std::ostream &operator<<(std::ostream &os, const Limit &limit);
};

#endif