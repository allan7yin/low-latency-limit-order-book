#include "Book.hpp"
#include "Order.hpp"
#include <iostream>

Book::Book() : buyTree(new RedBlackTree<Limit>()), sellTree(new RedBlackTree<Limit>()) {
}

Book::~Book() {
    for (auto &[id, order] : orderMap) {
        delete order;
    }
    orderMap.clear();
}

// PRIVATE
void Book::insertLimit(const int limitPrice, const bool buyOrSell) {
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->Insert(limitPrice, Limit(limitPrice, buyOrSell));
}

void Book::deleteLimit(const int limitPrice, const bool buyOrSell) {
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->Delete(limitPrice);
}

void Book::processMarketOrder(const int orderId, const bool buyOrSell, int shares) {
    auto bookEdge = buyOrSell ? getLowestSell() : getHighestBuy();
    while (bookEdge != nullptr && bookEdge->value.getHeadOrder()->getShares() <= shares) {
        Order *headOrder = bookEdge->value.getHeadOrder();
        shares -= headOrder->getShares();
        headOrder->remove();

        if (bookEdge->value.getSize() == 0) {
            deleteLimit(bookEdge->value.getLimitPrice(), bookEdge->value.getBuyOrSell());
        }

        orderMap.erase(headOrder->getId());
        executedOrdersCount++;
        bookEdge = buyOrSell ? getLowestSell() : getHighestBuy();
    }

    if (bookEdge != nullptr && shares != 0) {
        bookEdge->value.getHeadOrder()->partiallyFillOrder(shares);
        executedOrdersCount++;
    }
}

int Book::processLimitOrderInMarket(const int orderId, const bool buyOrSell, int shares, const int limitPrice) {
    if (buyOrSell) {
        auto lowestSell = getLowestSell();
        while (lowestSell != nullptr && shares != 0 && lowestSell->value.getLimitPrice() <= limitPrice) {
            if (shares <= lowestSell->value.getTotalVolume()) {
                processMarketOrder(orderId, buyOrSell, shares);
                return 0;
            } else {
                shares -= lowestSell->value.getTotalVolume();
                processMarketOrder(orderId, buyOrSell, lowestSell->value.getTotalVolume());
            }
            lowestSell = getLowestSell();
        }
        return shares;
    } else {
        auto highestBuy = getHighestBuy();
        while (highestBuy != nullptr && shares != 0 && highestBuy->value.getLimitPrice() >= limitPrice) {
            if (shares <= highestBuy->value.getLimitPrice()) {
                processMarketOrder(orderId, buyOrSell, shares);
                return 0;
            } else {
                shares -= highestBuy->value.getLimitPrice();
                processMarketOrder(orderId, buyOrSell, highestBuy->value.getLimitPrice());
            }
        }
        return shares;
    }
}

// PUBLIC
RedBlackTreeNode<Limit> *Book::getLowestSell() const {
    return this->sellTree->GetSmallestNode();
}

RedBlackTreeNode<Limit> *Book::getHighestBuy() const {
    return this->buyTree->GetLargestNode();
}

void Book::addMarketOrder(const int orderId, const bool buyOrSell, int shares) {
    executedOrdersCount = 0;
    auto tree = (buyOrSell) ? buyTree : sellTree;
    tree->RBTreeRebalanceCount = 0;
    processMarketOrder(orderId, buyOrSell, shares);
}

void Book::addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice) {

    shares = processLimitOrderInMarket(orderId, buyOrSell, shares, limitPrice);

    if (shares != 0) {
        Order *newOrder = new Order(orderId, buyOrSell, shares, limitPrice);
        orderMap[orderId] = newOrder;

        insertLimit(limitPrice, buyOrSell);
        auto tree = buyOrSell ? buyTree : sellTree;
        auto limitNode = tree->find(limitPrice);
        limitNode->value.addOrder(newOrder);
    }
}

void Book::cancelLimitOrder(int orderId) {
    executedOrdersCount = 0;
    Order *orderNode = searchOrderMap(orderId);

    if (orderNode != nullptr) {
        auto tree = (orderNode->getBuyOrSell()) ? buyTree : sellTree;
        tree->RBTreeRebalanceCount = 0;

        orderNode->remove();
        if (orderNode->getParentLimit()->getSize() == 0) {
            deleteLimit(orderNode->getLimit(), orderNode->getBuyOrSell());
        }

        orderMap.erase(orderId);
        delete orderNode;
    }
}

void Book::modifyLimitOrder(int orderId, int shares, int limitPrice) {
    Order *order = searchOrderMap(orderId);
    bool buyOrSell = order->getBuyOrSell();

    // there is no "modify" operation -> delete and then reinsert
    cancelLimitOrder(orderId);
    addLimitOrder(orderId, buyOrSell, shares, limitPrice);
}

Order *Book::searchOrderMap(int orderId) const {
    auto it = orderMap.find(orderId);
    if (it != orderMap.end()) {
        return it->second;
    } else {
        //        std::cout << "No order number " << orderId << std::endl;
        return nullptr;
    }
}

RedBlackTreeNode<Limit> *Book::searchLimitMaps(int limitPrice, bool buyOrSell) const {
    auto &tree = buyOrSell ? buyTree : sellTree;
    auto it = tree->find(limitPrice);
    if (it == nullptr) {
        std::cout << "No " << (buyOrSell ? "buy " : "sell ") << "limit at " << limitPrice << std::endl;
    }
    return it;
}

std::vector<int> Book::inOrderTreeTraversal(bool buyOrSell) {
    auto tree = (buyOrSell) ? buyTree : sellTree;
    std::vector<int> result;

    std::function<void(RedBlackTreeNode<Limit> *)> inOrderHelper = [&](RedBlackTreeNode<Limit> *node) {
        if (!node) {
            return;
        }
        inOrderHelper(node->left);
        result.push_back(node->value.getLimitPrice());
        inOrderHelper(node->right);
    };

    inOrderHelper(tree->getRoot());
    return result;
}

std::vector<int> Book::preOrderTreeTraversal(bool buyOrSell) {
    auto tree = (buyOrSell) ? buyTree : sellTree;
    std::vector<int> result;

    std::function<void(RedBlackTreeNode<Limit> *)> preOrderHelper = [&](RedBlackTreeNode<Limit> *node) {
        if (!node) {
            return;
        }
        result.push_back(node->value.getLimitPrice());
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    };

    preOrderHelper(tree->getRoot());
    return result;
}

std::vector<int> Book::postOrderTreeTraversal(bool buyOrSell) {
    auto tree = (buyOrSell) ? buyTree : sellTree;
    std::vector<int> result;

    std::function<void(RedBlackTreeNode<Limit> *)> postOrderHelper = [&](RedBlackTreeNode<Limit> *node) {
        if (!node) {
            return;
        }
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        result.push_back(node->value.getLimitPrice());
    };

    postOrderHelper(tree->getRoot());
    return result;
}

Order *Book::getRandomOrder(std::mt19937 gen) const {
    if (orderMap.size() > 0) {
        std::uniform_int_distribution<> mapDist(0, (int)(orderMap.size() - 1));
        int randomIndex = mapDist(gen);

        auto it = orderMap.begin();
        std::advance(it, randomIndex);
        return it->second;
    }
    return nullptr;
}