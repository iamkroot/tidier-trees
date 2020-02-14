#ifndef BINTREE_H
#define BINTREE_H

#include <vector>
#include "Drawable.h"

class BinTree : Drawable {
    BinTree* left;
    BinTree* right;

public:
    BinTree();

    BinTree(BinTree* left, BinTree* right);

private:
    bool draw() override;
};

#endif //BINTREE_H
