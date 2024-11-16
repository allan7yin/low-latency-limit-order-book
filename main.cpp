#include "LimitOrderBook/Book.hpp"
#include "PerformanceTestingUtil/OrderExecutor.hpp"
#include "PerformanceTestingUtil/OrderGenerator.hpp"

#include <chrono>
#include <iostream>
#include <vector>

int main() {
    Book *book = new Book();
    OrderGenerator orderGenerator(book);
    OrderExecutor orderExecutor(book);

    orderGenerator.randomInitialOrders("/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/initialRandomOrders.txt", 10000, 500);

    auto start = std::chrono::high_resolution_clock::now();
    orderExecutor.loadOrdersFromFile("/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/initialRandomOrders.txt", "/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/initialPerformance.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cerr << "Total Time for Initial Orders: " << duration.count() << " ms" << std::endl;

    // create larger number of incoming orders
    orderGenerator.randomOrders("/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/randomOrders.txt", 1000000);
    start = std::chrono::high_resolution_clock::now();
    orderExecutor.loadOrdersFromFile("/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/randomOrders.txt",
                                     "/Users/allanyin/Developer/cs/low-latency-limit-order-book/generatedData/finalPerformanceMetrics.txt");

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cerr << "Total Time to Process Orders: " << duration.count() << " ms" << std::endl;

    delete book;
    return 0;
}