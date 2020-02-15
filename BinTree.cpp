#include "Line.h"
#include "Circle.h"
#include "BinTree.h"

BinTree::BinTree() : left(nullptr), right(nullptr) {};

BinTree::BinTree(BinTree *left, BinTree *right) : left(left), right(right) {}

BinTree::~BinTree() {
    if (left)
        left->~BinTree();
    if (right)
        right->~BinTree();
    left = right = nullptr;
}

void BinTree::setup(BinTree *tree, int level, BinTree::Extreme *lMost, BinTree::Extreme *rMost, int minSep) {
    if (not tree) {  // base case
        lMost->level = -1;
        rMost->level = -1;
        return;
    }
    tree->y = level;
    BinTree *l = tree->left;
    BinTree *r = tree->right;
    Extreme lr, ll, rr, rl;
    setup(l, level + 1, &ll, &lr, minSep);
    setup(r, level + 1, &rl, &rr, minSep);
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
    tree->offset = (rootSep + 1) / 2;
    lOffSum -= tree->offset;
    rOffSum += tree->offset;
    if (rl.level > ll.level or not tree->left) {
        lMost->update(&rl);
        lMost->offset += tree->offset;
    } else {
        lMost->update(&ll);
        lMost->offset -= tree->offset;
    }
    if (lr.level > rr.level or not tree->right) {
        rMost->update(&lr);
        rMost->offset -= tree->offset;
    } else {
        rMost->update(&rr);
        rMost->offset += tree->offset;
    }

    if (l and l != tree->left) {
        rr.node->threaded = true;
        rr.node->offset = abs(rr.offset + tree->offset - lOffSum);
        if (lOffSum - tree->offset <= rr.offset) {
            rr.node->left = l;
        } else {
            rr.node->right = l;
        }
    } else if (r and r != tree->right) {
        ll.node->threaded = true;
        ll.node->offset = abs(ll.offset - tree->offset - rOffSum);
        if (rOffSum + tree->offset >= ll.offset) {
            ll.node->right = r;
        } else {
            ll.node->left = r;
        }
    }
}

void BinTree::petrify(BinTree *tree, int x) {
    if (not tree)
        return;
    tree->x = x;
    if (tree->threaded) {
        tree->threaded = false;
        tree->right = tree->left = nullptr;
    }
    petrify(tree->left, x - tree->offset);
    petrify(tree->right, x + tree->offset);
}

bool BinTree::draw() {
    Extreme lm, rm;
    setup(this, 0, &lm, &rm, 100);
    petrify(this, 300);
    draw(this);
    return true;
}

void BinTree::draw(BinTree *tree) {
    if (not tree)
        return;
    Circle c = Circle({static_cast<GLuint>(tree->x), static_cast<GLuint>(tree->y * 50 + 200)}, 20);
    c.draw();
    if (tree->left) {
        Line l = Line({tree->x, tree->y * 50 + 200}, {tree->left->x, tree->left->y * 50 + 200});
        l.draw();
        draw(tree->left);
    }
    if (tree->right) {
        Line l = Line({tree->x, tree->y * 50 + 200}, {tree->right->x, tree->right->y * 50 + 200});
        l.draw();
        draw(tree->right);
    }
}
