#include "Order.hpp"

Order::Order(int id, bool buyOrSell, int shares, int limit, int entryTime, int eventTime)
    : id(id), buyOrSell(buyOrSell), shares(shares), limit(limit), entryTime(entryTime), eventTime(eventTime) {}

int Order::getOrderId() const {
    return id;
}

int Order::getShares() const {
    return shares;
}

bool Order::getBuyOrSell() const {
    return buyOrSell;
}

int Order::getLimit() const {
    return limit;
}
