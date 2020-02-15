#ifndef BINTREE_H
#define BINTREE_H

#include <vector>
#include "Drawable.h"

class BinTree : Drawable {
    BinTree *left;
    BinTree *right;
    int x{}, y{};
    int offset{};
    bool threaded{};

    class Extreme {
    public:
        BinTree *node;
        int offset;
        int level;

        Extreme() : node(nullptr), offset(-1), level(-1) {}

        void update(Extreme *other) {
            this->node = other->node;
            this->offset = other->offset;
            this->level = other->level;
        }
    };

    static void setup(BinTree *tree, int level, Extreme *lMost, Extreme *rMost, int minSep);

    static void petrify(BinTree *tree, int x);

    static void draw(BinTree *tree);

public:
    BinTree();

    BinTree(BinTree *left, BinTree *right);

    virtual ~BinTree();

    bool draw() override;
};

#endif //BINTREE_H
