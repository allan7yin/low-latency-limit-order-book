#include "Order.hpp"

int Order::getId() const {
    return id;
}

bool Order::getBuyOrSell() const {
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

Limit *Order::getParentLimit() const {
    return parentLimit;
}

void Order::partiallyFillOrder(int orderShares) {
    shares -= orderShares;
    parentLimit->partiallyFillVolume(orderShares);
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "Order ID: " << order.id << ", "
       << "Shares: " << order.shares << ", "
       << "Limit: " << order.limit << ", "
       << "Entry Time: " << order.entryTime << ", "
       << "Event Time: " << order.eventTime;
    return os;
}

Order::Order(int id, bool buyOrSell, int shares, int limit, int entryTime, int eventTime)
    : id(id),
      buyOrSell(buyOrSell),
      shares(shares),
      limit(limit),
      entryTime(entryTime),
      eventTime(eventTime),
      parentLimit(nullptr) {
}