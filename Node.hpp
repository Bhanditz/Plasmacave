#ifndef NODE_HPP
#define NODE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#include "Common.hpp"

class Node {
 private:
 public:
    bool hit;
    Node(bool _hit = false) : hit(_hit) {}
};

#endif
