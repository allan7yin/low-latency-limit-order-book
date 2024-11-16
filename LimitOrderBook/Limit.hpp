#ifndef limit_hpp
#define limit_hpp

#include <iostream>

class Order;
class Book;

class Limit {
  private:
    int limitPrice;
    bool buyOrSell;
    int size;
    int totalVolume;
    Order *headOrder;
    Order *tailOrder;

  public:
    Limit(int limitPrice, bool buyOrSell, int size = 0, int totalVolume = 0);
    ~Limit();

    int getLimitPrice() const;
    int getSize() const;
    int getTotalVolume() const;
    bool getBuyOrSell() const;
    Order *getHeadOrder() const;
    Order *getTailOrder() const;

    void addOrder(Order *order);
    void partiallyFillVolume(int orderShares);
    void addShares(int shares);

    void printForward() const;
    void printBackward() const;
    friend std::ostream &operator<<(std::ostream &os, const Limit &limit);
    friend class Order;
};

#endif