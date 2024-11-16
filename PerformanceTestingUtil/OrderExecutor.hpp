#ifndef ORDEREXECUTOR_HPP
#define ORDEREXECUTOR_HPP

#include "../LimitOrderBook/Book.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

class Book;

class OrderExecutor {
  private:
    Book *book;

    using OrderFunction = void (OrderExecutor::*)(std::istringstream &);
    std::unordered_map<std::string_view, OrderFunction> orderFunctions;

    void loadMarketOrder(std::istringstream &iss);
    void loadAddLimitOrder(std::istringstream &iss);
    void loadCancelLimitOrder(std::istringstream &iss);
    void loadModifyLimitOrder(std::istringstream &iss);

  public:
    OrderExecutor(Book *book);
    void loadOrdersFromFile(const std::string &inputFile, const std::string &outputFile);
};

#endif