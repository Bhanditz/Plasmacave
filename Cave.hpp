#ifndef CAVE_HPP
#define CAVE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#define MAP_MAX_SIZE 10

Uint32 min(Uint32 a, Uint32 b) { return a<b?a:b; }
Uint32 max(Uint32 a, Uint32 b) { return a>b?a:b; }

struct Node {
    Node() {};
};

class Cave {
 private:
    Node nodes[MAP_MAX_SIZE][MAP_MAX_SIZE][MAP_MAX_SIZE];
 public:
    const Uint32 width, height, depth; //voipi olla public, koska const ja konstruktori vaatii

    Cave(Uint32 s = MAP_MAX_SIZE) : width(min(s, MAP_MAX_SIZE)), height(min(s, MAP_MAX_SIZE)), depth(min(s, MAP_MAX_SIZE)) {
        Cave(s, s, s);
    }

    Cave(Uint32 w, Uint32 h, Uint32 d = MAP_MAX_SIZE) : width(min(w, MAP_MAX_SIZE)), height(min(h, MAP_MAX_SIZE)), depth(min(d, MAP_MAX_SIZE)) {
        for(Uint32 z = 0; z < d; z++) {
            for(Uint32 y = 0; y < h; y++) {
                for(Uint32 x = 0; x < w; x++) {
                    this->nodes[d][y][x] = Node();
                }
            }
        }
    }

    void draw() {
//        glTranslated( -this->width/2.0, 0.0, -this->depth/2.0 );

        double xx;
        double zz;

        for(Uint32 z = 0; z < this->depth; z++) {
            for(Uint32 x = 0; x < this->width; x++) {

                xx = x-((double)this->width/2.0);
                zz = z-((double)this->depth/2.0);

                if ((x+z)%2) {
                    glColor3d(1, 0, 0);
                } else {
                    glColor3d(1, 1, 1);
                }

                glBegin(GL_QUADS);
                    glVertex3d(xx-0.5, -1.0, zz-0.5);
                    glVertex3d(xx+0.5, -1.0, zz-0.5);
                    glVertex3d(xx+0.5, -1.0, zz+0.5);
                    glVertex3d(xx-0.5, -1.0, zz+0.5);
                glEnd();
            }
        }
    }
};

#endif
