#include "BinTree.h"

BinTree::BinTree(): left(nullptr), right(nullptr) {};

BinTree::BinTree(BinTree* left, BinTree* right) : left(left), right(right) {}

bool BinTree::draw() {
    return false;
}
