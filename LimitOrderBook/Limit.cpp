#include "Limit.hpp"
#include "Order.hpp"
#include <iostream>

Limit::Limit(int limitPrice, bool buyOrSell, int size, int totalVolume)
    : limitPrice(limitPrice), buyOrSell(buyOrSell), size(size), totalVolume(totalVolume), headOrder(nullptr), tailOrder(nullptr) {}

Limit::~Limit() {}

int Limit::getLimitPrice() const {
    return this->limitPrice;
}

int Limit::getSize() const {
    return this->size;
}

int Limit::getTotalVolume() const {
    return this->totalVolume;
}

bool Limit::getBuyOrSell() const {
    return this->buyOrSell;
}

void Limit::addOrder(Order *order) {
    if (!headOrder) {
        headOrder = tailOrder = order;
    } else {
        tailOrder->nextOrder = order;
        order->prevOrder = tailOrder;
        order->nextOrder = nullptr;
        tailOrder = order;
    }
    size += 1;
    totalVolume += order->getShares();
    order->parentLimit = this;
}

void Limit::partiallyFillVolume(int orderShares) {
    this->totalVolume -= orderShares;
}

void Limit::addShares(int shares) {
    this->totalVolume += shares;
}

Order *Limit::getHeadOrder() const {
    return headOrder;
}

Order *Limit::getTailOrder() const {
    return tailOrder;
}

void Limit::printForward() const {
    auto curr = headOrder;
    while (curr) {
        std::cout << curr->getId() << std::endl;
        curr = curr->nextOrder;
    }
}

void Limit::printBackward() const {
    auto curr = tailOrder;
    while (curr) {
        std::cout << curr->getId() << std::endl;
        curr = curr->prevOrder;
    }
}

std::ostream &operator<<(std::ostream &os, const Limit &limit) {
    os << "LimitPrice: " << limit.limitPrice << ", "
       << (limit.buyOrSell ? "Buy" : "Sell") << ", "
       << "Size: " << limit.size << ", "
       << "TotalVolume: " << limit.totalVolume;
    return os;
}