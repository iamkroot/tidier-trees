#ifndef LINE_H
#define LINE_H

#include <vector>
#include "Vertex2D.h"

class Line : Drawable {
    Vertex2D start, end;
    std::vector<Vertex2D> points;
public:
    Line(const Vertex2D &start, const Vertex2D &end);

    virtual ~Line();

    /**
     * @brief Rasterize line using Bresenham's midpoint algorithm
     * @return Success
     */
    std::vector<Vertex2D> fillPoints();

    bool draw() override;
};

#endif //LINE_H
