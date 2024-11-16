#include "Order.hpp"
#include "Limit.hpp"

Order::Order(int id, bool buyOrSell, int shares, int limit, int entryTime,
             int eventTime)
    : id(id), buyOrSell(buyOrSell), shares(shares), limit(limit),
      entryTime(entryTime), eventTime(eventTime), parentLimit(nullptr) {}

int Order::getId() const {
    return id;
}

int Order::getShares() const {
    return shares;
}

int Order::getLimit() const {
    return limit;
}

bool Order::getBuyOrSell() const {
    return buyOrSell;
}

Limit *Order::getParentLimit() const {
    return parentLimit;
}

int Order::getEntryTime() const {
    return entryTime;
}

int Order::getEventTime() const {
    return eventTime;
}

void Order::process() {
    if (!prevOrder) {
        if (nextOrder == nullptr) {
            parentLimit->headOrder = nullptr;
            parentLimit->tailOrder = nullptr;
        } else {
            parentLimit->headOrder = nextOrder;
            nextOrder->prevOrder = nullptr;
        }

        parentLimit->size--;
        parentLimit->totalVolume -= shares;
    }
}

void Order::remove() {
    if (prevOrder == nullptr) {
        parentLimit->headOrder = nextOrder;
    } else {
        prevOrder->nextOrder = nextOrder;
    }
    if (nextOrder == nullptr) {
        parentLimit->tailOrder = prevOrder;
    } else {
        nextOrder->prevOrder = prevOrder;
    }

    parentLimit->size--;
    parentLimit->totalVolume -= shares;
}

void Order::partiallyFillOrder(int orderShares) {
    shares -= orderShares;
    parentLimit->partiallyFillVolume(orderShares);
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "Order ID: " << order.getId() << ", "
       << "Shares: " << order.getShares() << ", "
       << "Limit: " << order.getLimit() << ", "
       << "Entry Time: " << order.getEntryTime() << ", "
       << "Event Time: " << order.getEntryTime();
    return os;
}