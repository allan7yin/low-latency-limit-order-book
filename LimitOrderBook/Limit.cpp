#include "Limit.hpp"
#include <iostream>

Limit::Limit(int limitPrice, bool buyOrSell, int size, int totalVolume) : limitPrice(limitPrice), buyOrSell(buyOrSell), size(size), totalVolume(totalVolume), orders(new DoublyLinkedList<Order *>()) {}

Limit::~Limit() {
    if (orders) {
        delete orders;
    }
}

Order *Limit::getHeadOrder() {
    return (size > 0) ? this->orders->getStart()->value : nullptr;
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
    auto *newNode = new DoublyLinkedListNode<Order *>(order);
    this->orders->Insert(newNode);
}

void Limit::removeOrder(DoublyLinkedListNode<Order *> *node) {
    size--;
    totalVolume -= node->value->getShares();
    orders->Delete(node);
}

void Limit::partiallyFillVolume(int orderShares) {
    this->totalVolume -= orderShares;
}

void Limit::addShares(int shares) {
    this->totalVolume += shares;
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