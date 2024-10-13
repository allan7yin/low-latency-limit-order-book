#ifndef book_hpp
#define book_hpp

#include "../RedBlackTree/RedBlackTree.hpp"
#include "Limit.hpp"

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

  public:
    ~Book();
};

#endif