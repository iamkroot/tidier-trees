#ifndef VERTEX2D_H
#define VERTEX2D_H

#include "Drawable.h"

class Vertex2D : Drawable {
    GLuint x, y;
public:
    Vertex2D(GLuint x, GLuint y);

    Vertex2D(int x, int y);

    virtual ~Vertex2D();

    GLuint getX() const;

    GLuint getY() const;

    void setX(GLuint val);

    void setY(GLuint val);

    bool draw() override;
};

#endif //VERTEX2D_H
