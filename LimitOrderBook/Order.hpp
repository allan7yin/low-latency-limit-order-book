#ifndef order_hpp
#define order_hpp

#include "Limit.hpp"
#include <iostream>

class Limit;

class Order {
  private:
    int id;
    bool buyOrSell;
    int shares;
    int limit;
    int entryTime;
    int eventTime;
    Limit *parentLimit;

  public:
    Order(int id, bool buyOrSell, int shares, int limit, int entryTime = 0, int eventTime = 0);
    int getId() const;
    bool getBuyOrSell() const;
    int getShares() const;
    int getLimit() const;
    int getEntryTime() const;
    int getEventTime() const;
    Limit *getParentLimit() const;
    void partiallyFillOrder(int orderShares);

    friend std::ostream &operator<<(std::ostream &os, const Order &order);
};

#endif