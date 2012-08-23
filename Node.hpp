#ifndef NODE_HPP
#define NODE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#include "Common.hpp"

class Node {
 private:
    double elevation;
 public:
    Node(double _elevation = 0.0) : elevation(_elevation) {}

    void   setElevation(double _elevation) { this->elevation = _elevation; }
    double getElevation()                  { return this->elevation; }
};

#endif
