#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "Drawable.h"
#include "Vertex2D.h"

class Circle : Drawable {
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
     * @brief Rasterize circle using midpoint algorithm
     * @return Success
     */
    bool fillPoints();

    bool draw() override;

};

#endif //CIRCLE_H
