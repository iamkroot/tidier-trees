#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <vector>
#include "Vertex2D.h"
#include "Line.h"
#include "Circle.h"

/**
 * @brief Class to represent a binary tree
 */
class BinTree {
    BinTree* left;
    BinTree* right;
    Vertex2D* center{};
    int offset{};
    bool threaded{};

    /**
     * @brief Record of the leftmost/rightmost node in a subtree
     * @param node Pointer to the node
     * @param offset The horizontal offset of the node
     * @param level The depth of the node
     */
    class Extreme {
    public:
        BinTree* node;
        int offset;
        int level;

        Extreme() : node(nullptr), offset(-1), level(-1) {}

        Extreme(const Extreme &other) = default;
    };

    Circle* circle{};
    std::vector<Vertex2D> points;

    /**
     * @brief Do a post-order traversal of the tree and compute the horizontal offsets of siblings
     * @param tree The root node of the current subtree
     * @param level Current depth (root has 0 depth)
     * @param rMost Pointer to a record of the rightmost node in the left subtree
     * @param lMost Pointer to a record of the leftmost node in the right subtree
     */
    static void setup(BinTree* tree, int level, Extreme* rMost, Extreme* lMost);

    /**
     * @brief Compute the final x and y coordinates of the nodes
     * @param tree The root node of the current subtree
     * @param x The x coordinate
     * @param y The y coordinate
     * @param scaleY The scaling factor for the y coordinates
     */
    static void petrify(BinTree* tree, int x, int y, int scaleX, int scaleY);

public:

    BinTree(BinTree* left = nullptr, BinTree* right = nullptr);

    virtual ~BinTree();

    void setLeft(BinTree* left);

    void setRight(BinTree* right);

    bool draw();

    /**
     * @brief Rasterize the tree diagram
     * @param tree The root node of the tree to be rasterized
     * @return The entire set of points of the tree figure
     */
    std::vector<Vertex2D> fillPoints(BinTree* tree);

    std::string dumpTree();
};

/**
 * @brief Create a random binary tree structure
 * @param height The required height. If unspecified, it will be chosen to be a random int between 1 and 10
 * @param complete Whether to create a full binary tree (every internal node has two children)
 * @return The pointer to generated tree root node
 */
BinTree* genRandomTree(int height = -1, bool complete = false);

/**
 * @brief Some predefined trees
 * @return List of trees
 */
std::vector<BinTree*> genTrees();

#endif //BINTREE_H
