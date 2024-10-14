#include "Book.hpp"

RedBlackTree<Limit> *Book::getBuyTree() const {
    return this->buyTree;
}
RedBlackTree<Limit> *Book::getSellTree() const {
    return this->sellTree;
}

RedBlackTreeNode<Limit> *Book::getLowestSell() const {
    return this->sellTree;
}
RedBlackTreeNode<Limit> *getHighestBuy() const;