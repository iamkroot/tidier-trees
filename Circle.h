#ifndef CIRCLE_H
#define CIRCLE_H

#include <functional>
#include <vector>
#include "Vertex2D.h"

class Circle {
    Vertex2D center;
    GLuint radius;
    std::vector<Vertex2D> points;

    /**
     * @brief Draw the mirror points of the given point, using 8-way symmetry
     * @param x X coordinate
     * @param y Y coordinate
     */
    void drawSymmetricPoints(int x, int y);

public:
    Circle(const Vertex2D &center, GLuint radius);

    virtual ~Circle();

    /**
     * @brief Check whether the given point is interior to the circle
     * @param point Point to be checked
     * @return true if point is inside
     */
    [[nodiscard]] bool contains(const Vertex2D &point) const;

    /**
     * @brief Rasterize circle using midpoint algorithm
     * @param filter Callback function to determine whether point should be drawn or not
     * @return Success
     */
    std::vector<Vertex2D>
    fillPoints(const std::function<bool(Vertex2D)> &filter = [](const Vertex2D &p) { return true; });

    bool draw();

};

#endif //CIRCLE_H
