#include "Book.hpp"

Book::~Book() {
    if (buyTree) delete buyTree;
    if (sellTree) delete sellTree;
    if (stopSellTree) delete stopSellTree;
    if (stopBuyTree) delete stopBuyTree;
}