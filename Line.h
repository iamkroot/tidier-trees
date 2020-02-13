#ifndef LINE_H
#define LINE_H

#include "Vertex2D.h"
#include <vector>

class Line {
    Vertex2D start, end;
    std::vector<Vertex2D> points;
public:
    Line(const Vertex2D &start, const Vertex2D &end);

    virtual ~Line();

    bool fillPoints();

    bool draw();
};

#endif //LINE_H
