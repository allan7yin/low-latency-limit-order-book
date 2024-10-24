#include "../LimitOrderBook/RedBlackTree/RedBlackTree.hpp" // Include your Red-Black Tree header
#include <gtest/gtest.h>

// Test insertion into the Red-Black Tree
TEST(RedBlackTreeTest, InsertNodes) {
    RedBlackTree<int> tree;

    tree.Insert(1, 1);
    tree.Insert(2, 1);
    tree.Insert(3, 1);
    tree.Insert(4, 1);

    EXPECT_EQ(tree.GetLargestNode()->key, 4);

    tree.Insert(6, 1);
    tree.Insert(5, 1);

    EXPECT_EQ(tree.GetLargestNode()->key, 6);
}

// Test minimum node
TEST(RedBlackTreeTest, GetMinNode) {
    RedBlackTree<int> tree;

    tree.Insert(1, 1);
    tree.Insert(2, 1);
    tree.Insert(3, 1);

    EXPECT_EQ(tree.GetSmallestNode()->key, 1);

    tree.Delete(1);
    EXPECT_EQ(tree.GetSmallestNode()->key, 2);
}

// Test removal of nodes
TEST(RedBlackTreeTest, RemoveNodes) {
    RedBlackTree<int> tree;

    tree.Insert(1, 1);
    tree.Insert(2, 1);
    tree.Insert(3, 1);

    tree.Delete(2);
    EXPECT_EQ(tree.GetSmallestNode()->key, 1);

    tree.Delete(1);
    EXPECT_EQ(tree.GetSmallestNode()->key, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}