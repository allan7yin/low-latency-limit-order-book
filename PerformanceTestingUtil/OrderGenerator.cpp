#include "orderGenerator.hpp"
#include <algorithm>

OrderGenerator::OrderGenerator(Book *_book) : book(_book), gen(rd()) {}

void OrderGenerator::createMarketOrder() {
    std::uniform_int_distribution<> sharesSample(5, 5000);
    std::uniform_int_distribution<> buyOrSellSample(0, 1);

    int shares = sharesSample(gen);
    bool buyOrSell = buyOrSellSample(gen);

    file << "Market " << orderId << " " << buyOrSell << " " << shares
         << std::endl;
    book->addMarketOrder(orderId, buyOrSell, shares);
    orderId++;
}

void OrderGenerator::createLimitOrder() {
    std::uniform_int_distribution<> sharesDist(5, 5000);
    std::normal_distribution<> limitPriceDist(500, 50);
    std::uniform_int_distribution<> buyOrSellDist(0, 1);

    int shares = sharesDist(gen);
    bool buyOrSell = buyOrSellDist(gen);
    int limitPrice;

    if (buyOrSell) {
        do {
            limitPrice = (int)limitPriceDist(gen);
        } while (book->getLowestSell() != nullptr &&
                 limitPrice >= book->getLowestSell()->value.getLimitPrice());
    } else {
        do {
            limitPrice = (int)limitPriceDist(gen);
        } while (book->getHighestBuy() != nullptr &&
                 limitPrice <= book->getHighestBuy()->value.getLimitPrice());
    }

    file << "AddLimit " << orderId << " " << buyOrSell << " " << shares << " "
         << limitPrice << std::endl;
    book->addLimitOrder(orderId, buyOrSell, shares, limitPrice);
    orderId++;
}

void OrderGenerator::cancelLimitOrder() {
    Order *order = book->getRandomOrder(gen);

    if (order == nullptr) {
        createLimitOrder();
    } else {
        int orderId = order->getId();
        file << "CancelLimit " << orderId << std::endl;
        book->cancelLimitOrder(orderId);
    }
}

void OrderGenerator::createLimitInMarket() {
    std::uniform_int_distribution<> sharesDist(1, 1000);
    std::uniform_int_distribution<> buyOrSellDist(0, 1);

    int shares = sharesDist(gen);
    int limitPrice;
    bool buyOrSell = buyOrSellDist(gen);

    if (buyOrSell && book->getLowestSell() != nullptr) {
        limitPrice = book->getLowestSell()->value.getLimitPrice() + 1;
    } else if (!buyOrSell && book->getHighestBuy() != nullptr) {
        limitPrice = book->getHighestBuy()->value.getLimitPrice() - 1;
    } else {
        createLimitOrder();
        return;
    }

    file << "AddLimitInMarket " << orderId << " " << buyOrSell << " " << shares
         << " " << limitPrice << std::endl;
    book->addLimitOrder(orderId, buyOrSell, shares, limitPrice);
    orderId++;
}

void OrderGenerator::modifyLimitOrder() {
    std::uniform_int_distribution<> sharesDist(1, 1000);
    std::normal_distribution<> limitPriceDist(
        book->getHighestBuy() ? book->getHighestBuy()->value.getLimitPrice()
                              : 500,
        50);

    int shares = sharesDist(gen);

    Order *order = book->getRandomOrder(gen);

    if (order == nullptr) {
        createLimitOrder();
        return;
    }

    int orderId = order->getId();
    bool buyOrSell = order->getBuyOrSell();
    int limitPrice;

    if (buyOrSell) { // Buy order
        if (!book->getLowestSell()) {
            limitPrice =
                limitPriceDist(gen); // No sell tree, generate any valid price
        } else {
            int lowestSell = book->getLowestSell()->value.getLimitPrice();
            int maxAttempts = 10; // Prevent infinite loop
            do {
                limitPrice = std::clamp((int)limitPriceDist(gen), 1, lowestSell - 1);
                maxAttempts--;
            } while (limitPrice >= lowestSell && maxAttempts > 0);
            if (maxAttempts == 0) {
                limitPrice = lowestSell - 1; // Fallback
            }
        }
    } else { // Sell order
        if (!book->getHighestBuy()) {
            limitPrice = limitPriceDist(gen); // No buy tree, generate any valid price
        } else {
            int highestBuy = book->getHighestBuy()->value.getLimitPrice();
            int maxAttempts = 10; // Prevent infinite loop
            do {
                limitPrice =
                    std::clamp((int)limitPriceDist(gen), highestBuy + 1, INT_MAX);
                maxAttempts--;
            } while (limitPrice <= highestBuy && maxAttempts > 0);
            if (maxAttempts == 0) {
                limitPrice = highestBuy + 1; // Fallback
            }
        }
    }
    file << "ModifyLimit " << orderId << " " << shares << " " << limitPrice
         << std::endl;
    book->modifyLimitOrder(orderId, shares, limitPrice);
}

void OrderGenerator::randomOrders(const std::string &filePath,
                                  int numberOfOrders) {
    // Open a file named "orders.txt" for writing
    file.open(filePath);

    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::vector<double> probabilities = {0.05, 0.20, 0.60, 0.15};

    std::vector<std::function<void()>> actions = {
        std::bind(&OrderGenerator::createMarketOrder, this),
        std::bind(&OrderGenerator::createLimitOrder, this),
        std::bind(&OrderGenerator::cancelLimitOrder, this),
        std::bind(&OrderGenerator::createLimitInMarket, this),
        std::bind(&OrderGenerator::modifyLimitOrder, this)};
    std::partial_sum(probabilities.begin(), probabilities.end(),
                     probabilities.begin());

    // Generator the orders
    int batchsize = numberOfOrders / 1000;
    for (size_t i = 1; i < numberOfOrders + 1; i++) {
        double randNum = dis(gen);
        auto it =
            std::lower_bound(probabilities.begin(), probabilities.end(), randNum);
        int selectedIndex = (int)std::distance(probabilities.begin(), it);
        if (selectedIndex < probabilities.size()) {
            actions[selectedIndex]();
        }

        if (i % batchsize == 0) {
            std::cerr << "Sample generated " << i << std::endl;
        }
    }
    file.close();
    std::cerr << "Order generated." << std::endl;
}

void OrderGenerator::randomInitialOrders(const std::string &filePath,
                                         int numberOfOrders, int centreOfBook) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::uniform_int_distribution<> sharesDist(1, 1000);
    std::normal_distribution<> limitPriceDist(centreOfBook, 50);

    for (int order = 1; order <= numberOfOrders; ++order) {
        int shares = sharesDist(gen);
        int limitPrice = (int)limitPriceDist(gen);
        bool buyOrSell = limitPrice < centreOfBook;
        file << "AddLimit " << order << " " << buyOrSell << " " << shares << " "
             << limitPrice << std::endl;
    }
    file.close();
    std::cerr << "Initial Orders Generated." << std::endl;
}