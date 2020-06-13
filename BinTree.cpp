#include <iostream>
#include <random>
#include "GLUtils.h"
#include "BinTree.h"

BinTree::BinTree(BinTree* left, BinTree* right) : left(left), right(right) {
    center = new Vertex2D(0, 0);
}

BinTree::~BinTree() {
    delete left;
    delete right;
    delete center;
    delete circle;
    left = right = nullptr;
    center = nullptr;
    circle = nullptr;
}

void BinTree::setup(BinTree* tree, int level, Extreme* rMost, Extreme* lMost, int minSep) {
    if (not tree) {  // base case
        lMost->level = -1;
        rMost->level = -1;
        return;
    }

    BinTree* l = tree->left;
    BinTree* r = tree->right;
    Extreme lr, ll, rr, rl;
    setup(l, level + 1, &lr, &ll, minSep);
    setup(r, level + 1, &rr, &rl, minSep);

    if (not l and not r) {  // leaf node
        lMost->node = rMost->node = tree;
        lMost->level = rMost->level = level;
        lMost->offset = rMost->offset = 0;
        tree->offset = 0;
        return;
    }

    int curSep, rootSep, lOffSum, rOffSum;
    curSep = rootSep = minSep;
    lOffSum = rOffSum = 0;
    // increase the separation between left and right subtrees
    while (l and r) {
        if (curSep < minSep) {
            rootSep += minSep - curSep;
            curSep = minSep;
        }
        if (l->right) {
            lOffSum += l->offset;
            curSep -= l->offset;
            l = l->right;
        } else {
            lOffSum -= l->offset;
            curSep += l->offset;
            l = l->left;
        }
        if (r->left) {
            rOffSum -= r->offset;
            curSep -= r->offset;
            r = r->left;
        } else {
            rOffSum += r->offset;
            curSep += r->offset;
            r = r->right;
        }
    }

    tree->offset = rootSep / 2;
    lOffSum -= tree->offset;
    rOffSum += tree->offset;

    // store lowest nodes in left and right subtrees
    if (rl.level > ll.level or not tree->left) {
        *lMost = rl;
        lMost->offset += tree->offset;
    } else {
        *lMost = ll;
        lMost->offset -= tree->offset;
    }
    if (lr.level > rr.level or not tree->right) {
        *rMost = lr;
        rMost->offset -= tree->offset;
    } else {
        *rMost = rr;
        rMost->offset += tree->offset;
    }

    // thread the rightmost node in left subtree (l) and leftmost node in right subtree (r)
    if (l and l != tree->left) {
        rr.node->threaded = true;
        rr.node->offset = rr.offset + tree->offset - lOffSum;
        if (rr.node->offset >= 0) {  // thread as left child
            rr.node->left = l;
        } else {  // overlap detected, thread as right child and separate
            rr.node->right = l;
            rr.node->offset *= -1;
        }
    } else if (r and r != tree->right) {
        ll.node->threaded = true;
        ll.node->offset = ll.offset - tree->offset - rOffSum;
        if (ll.node->offset >= 0) {
            ll.node->left = r;
        } else {
            ll.node->right = r;
            ll.node->offset *= -1;
        }
    }
}

void BinTree::petrify(BinTree* tree, int x, int y, int scaleY) {
    if (not tree)
        return;
    tree->center->setX(x);
    tree->center->setY(y);
    if (tree->threaded) {  // delete the threads
        tree->threaded = false;
        tree->right = tree->left = nullptr;
    }
    petrify(tree->left, x - tree->offset, y + scaleY, scaleY);
    petrify(tree->right, x + tree->offset, y + scaleY, scaleY);
}

std::vector<Vertex2D> BinTree::fillPoints(BinTree* tree) {
    if (not tree)
        return {};
    tree->circle = new Circle(*tree->center, 15);
    auto circle_pts = tree->circle->fillPoints();
    points.insert(points.end(), circle_pts.begin(), circle_pts.end());
    if (tree->left) {
        fillPoints(tree->left);
        auto l = Line(*tree->center, *tree->left->center);
        auto line_pts = l.fillPoints(
                [tree](auto p) { return not(tree->circle->contains(p) or tree->left->circle->contains(p)); });
        points.insert(points.end(), line_pts.begin(), line_pts.end());
    }
    if (tree->right) {
        fillPoints(tree->right);
        auto l = Line(*tree->center, *tree->right->center);
        auto line_pts = l.fillPoints(
                [tree](auto p) { return not(tree->circle->contains(p) or tree->right->circle->contains(p)); });
        points.insert(points.end(), line_pts.begin(), line_pts.end());
    }
    return points;
}

bool BinTree::draw() {
    if (points.empty()) {
        Extreme rm, lm;
        setup(this, 0, &rm, &lm, 50);
        petrify(this, windowWidth / 2, 500, -50);
        fillPoints(this);
    }
    glBegin(GL_POINTS);
    for (const auto &point : points) {
        glVertex2i(point.getX(), point.getY());
    }
    glEnd();
    return true;
}

void BinTree::setLeft(BinTree* left) {
    BinTree::left = left;
}

void BinTree::setRight(BinTree* right) {
    BinTree::right = right;
}

BinTree* genRandomTree(int height, bool complete) {
    if (height < 0) {
        height = (int) std::random_device()() % 10;
    }
    if (not height)
        return nullptr;
    if (not complete and not(std::random_device()() % 5))
        return nullptr;
    auto tree = new BinTree();
    if (complete or std::random_device()() % 4) {
        tree->setLeft(genRandomTree(height - 1, complete));
    }
    if (complete or std::random_device()() % 4) {
        tree->setRight(genRandomTree(height - 1, complete));
    }
    return tree;
}

std::vector<BinTree*> genTrees() {
#define node new BinTree
    std::vector<BinTree*> trees{
            node(),
            node(node(), node()),
            node(node(node(), node()), node(node(), {})),
            node({}, node(node({}, node(node({}, node(node({}, node()), {})), {})), {})),  // thunderbolt
            genRandomTree(5, true),  // full tree of height 5
            node(genRandomTree(8, true), node(node(node(node(node(), {}), {}), {}), {}))
    };
#undef node
    return trees;
}