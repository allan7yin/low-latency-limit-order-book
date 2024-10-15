#include "Book.hpp"

// PRIVATE
DoublyLinkedListNode<Order *> *Book::findOrder(int orderId) const {
    auto it = orderMap.find(orderId);
    if (it != orderMap.end()) {
        return it->second;
    } else {
        std::cout << "No order number " << orderId << std::endl;
        return nullptr;
    }
}

void Book::insertLimit(const int limitPrice, const bool buyOrSell) {
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->Insert(limitPrice, new Limit(limitPrice, buyOrSell));
}
void Book::deleteLimit(const int limitPrice, const bool buyOrSell) {
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->Delete(limitPrice);
}

void Book::processMarketOrder(const int orderId, const bool buyOrSell, int shares) {
    auto bookEdge = buyOrSell ? getLowestSell() : getHighestBuy();
    while (bookEdge != nullptr && bookEdge->value->getHeadOrder()->getShares() <= shares) {
        DoublyLinkedListNode<Order *> *headOrder = bookEdge->value->getOrders()->getHeadNode();
        shares -= headOrder->value->getShares();
        headOrder->remove();

        if (bookEdge->value->getSize() == 0) {
            deleteLimit(bookEdge->value->getLimitPrice(), bookEdge->value->getBuyOrSell());
        }

        orderMap.erase(headOrder->value->getId());
        delete headOrder;
        executedOrdersCount++;
        bookEdge = buyOrSell ? getLowestSell() : getHighestBuy();
    }

    if (bookEdge != nullptr && shares != 0) {
        bookEdge->value->getHeadOrder()->partiallyFillOrder(shares);
        executedOrdersCount += 1;
    }
}

int Book::processLimitOrderInMarket(const int orderId, const bool buyOrSell, int shares, const int limitPrice) {
    if (buyOrSell) {
        auto lowestSell = getLowestSell();
        while (lowestSell != nullptr && shares != 0 && lowestSell->value->getLimitPrice() <= limitPrice) {
            if (shares <= lowestSell->value->getTotalVolume()) {
                processMarketOrder(orderId, buyOrSell, shares);
                return 0;
            } else {
                shares -= lowestSell->value->getTotalVolume();
                processMarketOrder(orderId, buyOrSell, lowestSell->value->getTotalVolume());
            }
            lowestSell = getLowestSell();
        }
        return shares;
    } else {
        auto highestBuy = getHighestBuy();
        while (highestBuy != nullptr && shares != 0 && highestBuy->value->getLimitPrice() >= limitPrice) {
            if (shares <= highestBuy->value->getTotalVolume()) {
                processMarketOrder(orderId, buyOrSell, shares);
                return 0;
            } else {
                shares -= highestBuy->value->getTotalVolume();
                processMarketOrder(orderId, buyOrSell, highestBuy->value->getTotalVolume());
            }
        }
        return shares;
    }
}

// PUBLIC
RedBlackTree<Limit *> *Book::getBuyTree() const {
    return this->buyTree;
}
RedBlackTree<Limit *> *Book::getSellTree() const {
    return this->sellTree;
}

RedBlackTreeNode<Limit *> *Book::getLowestSell() const {
    return this->sellTree->GetSmallestNode();
}
RedBlackTreeNode<Limit *> *Book::getHighestBuy() const {
    return this->buyTree->GetLargestNode();
}

void Book::addMarketOrder(const int orderId, const bool buyOrSell, int shares) {
    executedOrdersCount = 0;
    processMarketOrder(orderId, buyOrSell, shares);
}

void Book::addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice) {
    shares = processLimitOrderInMarket(orderId, buyOrSell, shares, limitPrice);

    if (shares != 0) {
        Order *newOrder = new Order(orderId, buyOrSell, shares, limitPrice);

        insertLimit(limitPrice, buyOrSell);
        auto &tree = buyOrSell ? buyTree : sellTree;
        auto limitNode = tree->find(limitPrice);
        limitNode->value->getOrders()->Insert(newOrder);
        orderMap[orderId] = limitNode->value->getOrders()->getTailNode();
    }
}

void Book::cancelLimitOrder(int orderId) {
    executedOrdersCount = 0;
    DoublyLinkedListNode<Order *> *orderNode = findOrder(orderId);

    if (orderNode != nullptr) {
        orderNode->remove();
        Limit *parentLimit = orderNode->value->getParentLimit();
        if (parentLimit->getSize() == 0) {
            deleteLimit(orderNode->value->getLimit(), parentLimit->getBuyOrSell());
        }

        orderMap.erase(orderId);
        delete orderNode;
    }
}

RedBlackTreeNode<Limit *> *Book::searchLimitMaps(int limitPrice, bool buyOrSell) const {
    auto &tree = buyOrSell ? buyTree : sellTree;
    auto it = tree->find(limitPrice);
    if (it == nullptr) {
        std::cout << "No " << (buyOrSell ? "buy " : "sell ") << "limit at " << limitPrice << std::endl;
    }
    return it;
}

// NEED MORE PUBLIC FUNCTIONS FOR TESTING