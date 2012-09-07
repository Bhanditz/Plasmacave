#ifndef NODE_HPP
#define NODE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#include "Common.hpp"

class Node {
 private:
    vec3 color;
    GLuint face;
 public:
    bool hit;
    Node(bool _hit = false) : hit(_hit) {}

    vec3 getColor() { return this->color; }

    void setColor(vec3 _color)
        { this->color = _color; }
    void setColor( double r, double g, double b )
        { setColor(vec3(r, g, b)); }

    void updateFace() {
        glNewList(this->face, GL_COMPILE);
            glColor3(this->color);
            glColor3d(1.0, 1.0, 1.0);
            drawCube(0.9);
        glEndList();
    }
    void draw() {
  //  printf("Drawing node (%f,%f,%f)\n", this->color.x, this->color.y, this->color.z);
       // glCallList(this->face);
    }
};

#endif
