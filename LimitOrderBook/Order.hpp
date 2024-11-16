#ifndef order_hpp
#define order_hpp

class Limit;

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
    Limit *parentLimit;

    friend class Limit;

  public:
    Order(int idNumber, bool buyOrSell, int shares, int limit, int entryTime = 0, int eventTime = 0);

    int getId() const;
    int getShares() const;
    int getLimit() const;
    int getEntryTime() const;
    int getEventTime() const;
    bool getBuyOrSell() const;
    Limit *getParentLimit() const;

    void process();
    void remove();
    void partiallyFillOrder(int orderShares);
};
#endif