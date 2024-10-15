#include "Limit.hpp"
#include <iostream>

Limit::Limit(int limitPrice, bool buyOrSell, int size, int totalVolume) : limitPrice(limitPrice), buyOrSell(buyOrSell), size(size), totalVolume(totalVolume) {}

Limit::~Limit() {
    if (orders) {
        delete orders;
    }
}

Order *Limit::getHeadOrder() {
    return this->orders->getStart()->value;
}

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

DoublyLinkedList<Order *> *Limit::getOrders() const {
    return this->orders;
}

void Limit::addOrder(Order *order) {
    this->orders->Insert(order);
}

void Limit::partiallyFillVolume(int orderShares) {
    this->totalVolume -= orderShares;
}

void Limit::printForward() const {
    auto curr = this->orders->getStart();
    while (curr) {
        std::cout << curr->value << std::endl;
        curr = curr->next;
    }
}

void Limit::printBackward() const {
    auto curr = this->orders->getEnd();
    while (curr) {
        std::cout << curr->value << std::endl;
        curr = curr->prev;
    }
}

std::ostream &operator<<(std::ostream &os, const Limit &limit) {
    os << "LimitPrice: " << limit.limitPrice << ", "
       << (limit.buyOrSell ? "Buy" : "Sell") << ", "
       << "Size: " << limit.size << ", "
       << "TotalVolume: " << limit.totalVolume;
    return os;
}