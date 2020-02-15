#ifndef LINE_H
#define LINE_H

#include <functional>
#include <vector>
#include "Vertex2D.h"

class Line {
    Vertex2D start, end;
    std::vector<Vertex2D> points;
public:
    Line(const Vertex2D &start, const Vertex2D &end);

    virtual ~Line();

    /**
     * @brief Rasterize line using Bresenham's midpoint algorithm
     * @param filter Callback function to determine whether point should be drawn or not
     * @return Success
     */
    std::vector<Vertex2D>
    fillPoints(const std::function<bool(Vertex2D)> &filter = [](const Vertex2D &p) { return true; });

    bool draw();
};

#endif //LINE_H
