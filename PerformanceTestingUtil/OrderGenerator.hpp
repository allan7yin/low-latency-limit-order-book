#ifndef ORDERGENERATOR_HPP
#define ORDERGENERATOR_HPP

#include "../LimitOrderBook/Book.hpp"
#include "../LimitOrderBook/Limit.hpp"
#include "../LimitOrderBook/Order.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>

class Book;

class Book;

class OrderGenerator {

  private:
    Book *book;
    int orderId = 1;
    std::ofstream file;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen;

    void createMarketOrder();
    void createLimitOrder();
    void cancelLimitOrder();
    void createLimitInMarket();
    void modifyLimitOrder();

  public:
    OrderGenerator(Book *book);
    void randomInitialOrders(const std::string &filePath, int numberOfOrders, int centreOfBook);
    void randomOrders(const std::string &filePath, int numberOfOrders);
};

#endif