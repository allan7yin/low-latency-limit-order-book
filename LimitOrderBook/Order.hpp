#ifndef ORDER_HPP
#define ORDER_HPP
class Order {
  private:
    int id;
    bool buyOrSell;
    int shares;
    int limit;
    int entryTime;
    int eventTime;
    Order *nextOrder;
    Order *prevOrder;

  public:
    Order(int id, bool buyOrSell, int shares, int limit, int entryTime, int eventTime);

    int getOrderId() const;
    int getShares() const;
    bool getBuyOrSell() const;
    int getLimit() const;
};

#endif