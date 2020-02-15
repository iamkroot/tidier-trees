#ifndef BINTREE_H
#define BINTREE_H

#include <vector>
#include "Drawable.h"
#include "Vertex2D.h"
#include "Line.h"
#include "Circle.h"

class BinTree : Drawable {
    BinTree *left;
    BinTree *right;
    Vertex2D *center{};
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

    std::vector<Vertex2D> points;

    static void setup(BinTree *tree, int level, Extreme *lMost, Extreme *rMost, int minSep);

    static void petrify(BinTree *tree, int x);

public:
    BinTree();

    BinTree(BinTree *left, BinTree *right);

    virtual ~BinTree();

    bool draw() override;

    std::vector<Vertex2D> fillPoints(BinTree *tree);
};

#endif //BINTREE_H
