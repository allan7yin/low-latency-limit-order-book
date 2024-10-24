#ifndef book_hpp
#define book_hpp

#include "Limit.hpp"
#include "RedBlackTree/RedBlackTree.hpp"
#include <unordered_map>

class Book {
  private:
    int executedOrdersCount;
    RedBlackTree<Limit *> *buyTree;
    RedBlackTree<Limit *> *sellTree;

    RedBlackTreeNode<Limit *> *highestBuy;
    RedBlackTreeNode<Limit *> *lowestSell;

    std::unordered_map<int, DoublyLinkedListNode<Order *> *> orderMap;

    DoublyLinkedListNode<Order *> *findOrder(int orderId) const;
    void insertLimit(const int limitPrice, const bool buyOrSell);
    void deleteLimit(const int limitPrice, const bool buyOrSell);
    void processMarketOrder(const int orderId, const bool buyOrSell, int shares);
    int processLimitOrderInMarket(int orderId, bool buyOrSell, int shares, int limitPrice);

  public:
    RedBlackTree<Limit *> *getBuyTree() const;
    RedBlackTree<Limit *> *getSellTree() const;
    RedBlackTreeNode<Limit *> *getLowestSell() const;
    RedBlackTreeNode<Limit *> *getHighestBuy() const;
    void addMarketOrder(int orderId, bool buyOrSell, int shares);
    void addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice);
    void cancelLimitOrder(int orderId);

    RedBlackTreeNode<Limit *> *searchLimitMaps(int limitPrice, bool buyOrSell) const;

    ~Book();
};

#endif