#include "Limit.hpp"

Limit::Limit(int limitPrice, int size, int totalVolume) : limitPrice(limitPrice), size(size), totalVolume(totalVolume) {}

Limit::~Limit() {
    if (headOrder) {
        delete headOrder;
    }
}