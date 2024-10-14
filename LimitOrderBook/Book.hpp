#ifndef book_hpp
#define book_hpp

#include "../RedBlackTree/RedBlackTree.hpp"
#include "Limit.hpp"
#include <unordered_map>

class Book {
  private:
    RedBlackTree<Limit> *buyTree;
    RedBlackTree<Limit> *sellTree;
    RedBlackTree<Limit> *stopSellTree;
    RedBlackTree<Limit> *stopBuyTree;

    RedBlackTreeNode<Limit> *highestBuy;
    RedBlackTreeNode<Limit> *lowestSell;
    RedBlackTreeNode<Limit> *highestStopSell;
    RedBlackTreeNode<Limit> *lowestStopBuy;

    std::unordered_map<int, Order *> orderMap;

    void insertLimit(int limitPrice, bool buyOrSell);
    void deleteLimit(int limitPrice, bool buyOrSell);
    void processMarketOrder(int orderId, bool buyOrSell, int shares);
    int processLimitOrderInMarket(int orderId, bool buyOrSell, int shares, int limitPrice);

  public:
    RedBlackTree<Limit> *getBuyTree() const;
    RedBlackTree<Limit> *getSellTree() const;
    RedBlackTreeNode<Limit> *getLowestSell() const;
    RedBlackTreeNode<Limit> *getHighestBuy() const;
    ~Book();
};

#endif