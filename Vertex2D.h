#ifndef VERTEX2D_H
#define VERTEX2D_H

#include <GL/gl.h>

class Vertex2D {
    GLuint x, y;
public:
    Vertex2D(GLuint x, GLuint y);

    virtual ~Vertex2D();

    GLuint getX() const;

    GLuint getY() const;

    bool draw();
};

#endif //VERTEX2D_H
