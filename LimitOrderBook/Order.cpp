#include "Order.hpp"

int Order::getId() const {
    return id;
}

bool Order::isBuyOrSell() const {
    return buyOrSell;
}

int Order::getShares() const {
    return shares;
}

int Order::getLimit() const {
    return limit;
}

int Order::getEntryTime() const {
    return entryTime;
}

int Order::getEventTime() const {
    return eventTime;
}

void Order::partiallyFillOrder(int orderShares) {
    shares -= orderShares;
    parentLimit->partiallyFillVolume(orderShares);
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "Order ID: " << order.id << ", "
       << (order.buyOrSell ? "Buy" : "Sell") << ", "
       << "Shares: " << order.shares << ", "
       << "Limit: " << order.limit << ", "
       << "Entry Time: " << order.entryTime << ", "
       << "Event Time: " << order.eventTime;
    return os;
}