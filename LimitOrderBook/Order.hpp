#ifndef order_hpp
#define order_hpp

#include <iostream>

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
    int getId() const;
    bool isBuyOrSell() const;
    int getShares() const;
    int getLimit() const;
    int getEntryTime() const;
    int getEventTime() const;
    void partiallyFillOrder(int orderShares);
    void process();
    void remove();

    friend std::ostream &operator<<(std::ostream &os, const Order &order);
};

#endif