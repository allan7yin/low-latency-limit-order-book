#ifndef book_hpp
#define book_hpp

#include "Limit.hpp"
#include "RedBlackTree/RedBlackTree.hpp"
#include <random>
#include <unordered_map>

class Book {
  private:
    RedBlackTree<Limit> *buyTree;
    RedBlackTree<Limit> *sellTree;

    std::unordered_map<int, Order *> orderMap;

    void insertLimit(const int limitPrice, const bool buyOrSell);
    void deleteLimit(const int limitPrice, const bool buyOrSell);
    void processMarketOrder(const int orderId, const bool buyOrSell, int shares);
    int processLimitOrderInMarket(int orderId, bool buyOrSell, int shares, int limitPrice);

  public:
    Book();
    ~Book();

    int executedOrdersCount = 0;

    RedBlackTreeNode<Limit> *getLowestSell() const;
    RedBlackTreeNode<Limit> *getHighestBuy() const;

    void addMarketOrder(int orderId, bool buyOrSell, int shares);
    void addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice);
    void modifyLimitOrder(int orderId, int shares, int limitPrice);
    void cancelLimitOrder(int orderId);

    Order *searchOrderMap(int orderId) const;
    RedBlackTreeNode<Limit> *searchLimitMaps(int limitPrice, bool buyOrSell) const;
    Order *getRandomOrder(std::mt19937 gen) const;

    std::vector<int> inOrderTreeTraversal(bool buyOrSell);
    std::vector<int> preOrderTreeTraversal(bool buyOrSell);
    std::vector<int> postOrderTreeTraversal(bool buyOrSell);
};

#endif