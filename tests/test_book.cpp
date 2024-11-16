#include "../LimitOrderBook/Book.hpp"
#include "../LimitOrderBook/Limit.hpp"
#include "../LimitOrderBook/Order.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Create Orders
TEST(LimitOrderBookTests, TestAddingAnOrder) {
    Book book;

    EXPECT_EQ(book.searchOrderMap(357), nullptr);
    EXPECT_EQ(book.searchLimitMaps(100, true), nullptr);

    book.addLimitOrder(357, true, 27, 100);

    EXPECT_EQ(book.searchOrderMap(357)->getShares(), 27);
    EXPECT_EQ(book.searchLimitMaps(100, true)->value.getTotalVolume(), 27);
    EXPECT_EQ(book.searchLimitMaps(20, false), nullptr);

    book.addLimitOrder(222, false, 35, 110);

    EXPECT_EQ(book.searchLimitMaps(110, false)->value.getTotalVolume(), 35);
}

TEST(LimitOrderBookTests, TestMultipleOrdersInALimit) {
    Book book;
    book.addLimitOrder(5, true, 80, 20);

    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getTotalVolume(), 80);
    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getSize(), 1);

    book.addLimitOrder(6, true, 32, 20);

    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getTotalVolume(), 112);
    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getSize(), 2);

    book.addLimitOrder(7, true, 111, 20);

    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getTotalVolume(), 223);
    EXPECT_EQ(book.searchLimitMaps(20, true)->value.getSize(), 3);
}

// // Cancel Orders
TEST(LimitOrderBookTests, TestCancelOrderLeavingNonEmptyLimit) {
    Book *book = new Book();
    book->addLimitOrder(5, true, 80, 20);
    book->addLimitOrder(6, true, 32, 20);
    book->addLimitOrder(7, true, 111, 20);

    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getSize(), 3);
    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getTotalVolume(), 223);

    book->cancelLimitOrder(6);

    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getSize(), 2);
    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getTotalVolume(), 191);

    book->cancelLimitOrder(7);

    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getSize(), 1);
    EXPECT_EQ(book->searchLimitMaps(20, true)->value.getTotalVolume(), 80);
}

TEST(LimitOrderBookTests, TestLimitHeadOrderChangeOnOrderCancel) {
    Book book = Book();
    book.addLimitOrder(5, true, 80, 20);
    book.addLimitOrder(6, true, 32, 20);
    book.addLimitOrder(7, true, 111, 20);

    Limit &limit = book.searchLimitMaps(20, true)->value;

    EXPECT_EQ(limit.getHeadOrder()->getId(), 5);

    book.cancelLimitOrder(5);

    EXPECT_EQ(limit.getHeadOrder()->getId(), 6);
}

TEST(LimitOrderBookTests, TestLimitHeadOrderChangeOnOrderCancelLeavingEmptyLimit) {
    Book *book = new Book();
    book->addLimitOrder(5, true, 80, 20);

    Limit &limit = book->searchLimitMaps(20, true)->value;

    EXPECT_EQ(limit.getHeadOrder()->getId(), 5);

    book->cancelLimitOrder(5);
    EXPECT_EQ(book->searchLimitMaps(20, true), nullptr);
}

TEST(LimitOrderBookTests, TestCancelOrderLeavingEmptyLimit) {
    Book book = Book();
    book.addLimitOrder(5, true, 80, 20);
    book.addLimitOrder(6, true, 80, 15);

    RedBlackTreeNode<Limit> *node1 = book.searchLimitMaps(20, true);
    RedBlackTreeNode<Limit> *node2 = book.searchLimitMaps(15, true);

    EXPECT_EQ(node2->value.getHeadOrder()->getId(), 6);
    EXPECT_EQ(node1->left->value.getLimitPrice(), 15);

    book.cancelLimitOrder(6);

    EXPECT_EQ(book.searchLimitMaps(15, true), nullptr);
    EXPECT_EQ(node1->left, nullptr);
}

TEST(LimitOrderBookTests, TestCorrectLimitParent) {
    Book *book = new Book();
    book->addLimitOrder(5, true, 80, 20);
    book->addLimitOrder(6, true, 80, 15);
    book->addLimitOrder(7, true, 80, 25);

    auto limit1 = book->searchLimitMaps(20, true);
    auto limit2 = book->searchLimitMaps(15, true);
    auto limit3 = book->searchLimitMaps(25, true);

    EXPECT_EQ(limit1->parent, nullptr);
    EXPECT_EQ(limit2->parent->value.getLimitPrice(), 20);
    EXPECT_EQ(limit3->parent->value.getLimitPrice(), 20);
    delete book;
}

TEST(LimitOrderBookTests, TestCorrectLimitChildren) {
    Book *book = new Book();
    book->addLimitOrder(5, true, 80, 20);
    book->addLimitOrder(6, true, 80, 15);
    book->addLimitOrder(7, true, 80, 25);

    auto limit1 = book->searchLimitMaps(20, true);
    auto limit2 = book->searchLimitMaps(15, true);

    EXPECT_EQ(limit1->left->value.getLimitPrice(), 15);
    EXPECT_EQ(limit1->right->value.getLimitPrice(), 25);
    EXPECT_EQ(limit2->left, nullptr);
    EXPECT_EQ(limit2->right, nullptr);
}

TEST(LimitOrderBookTests, TestBinarySearchTree) {
    Book *book = new Book();
    book->addLimitOrder(5, false, 80, 20);
    book->addLimitOrder(6, false, 80, 15);
    book->addLimitOrder(7, false, 80, 25);
    book->addLimitOrder(8, false, 80, 10);
    book->addLimitOrder(9, false, 80, 19);

    std::vector<int> expectedInOrder = {10, 15, 19, 20, 25};
    std::vector<int> actualInOrder = book->inOrderTreeTraversal(false);

    EXPECT_EQ(expectedInOrder, actualInOrder);

    std::vector<int> expectedPreOrder = {20, 15, 10, 19, 25};
    std::vector<int> actualPreOrder = book->preOrderTreeTraversal(false);

    EXPECT_EQ(expectedPreOrder, actualPreOrder);

    std::vector<int> expectedPostOrder = {10, 19, 15, 25, 20};
    std::vector<int> actualPostOrder = book->postOrderTreeTraversal(false);

    EXPECT_EQ(expectedPostOrder, actualPostOrder);
}

TEST(LimitOrderBookTests, TestModifyLimitOrder) {
    Book *book = new Book();
    book->addLimitOrder(5, true, 80, 20);
    book->addLimitOrder(6, true, 80, 15);
    book->addLimitOrder(7, true, 80, 25);

    auto limit1 = book->searchLimitMaps(20, true);

    book->modifyLimitOrder(5, 100, 20);
    book->modifyLimitOrder(6, 200, 20);
    book->modifyLimitOrder(7, 300, 20);

    EXPECT_EQ(limit1->parent, nullptr);
    EXPECT_EQ(limit1->value.getTotalVolume(), 600);
    delete book;
}