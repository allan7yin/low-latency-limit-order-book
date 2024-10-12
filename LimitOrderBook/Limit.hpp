#ifndef limit_hpp
#define limit_hpp

#include "Order.hpp"

class Limit {
  private:
    int limitPrice;
    int size;
    int totalVolume;
    Order *headOrder;
    Order *tailOrder;

  public:
    Limit(int limitPrice, int size, int totalVolume);
    ~Limit();
};

#endif