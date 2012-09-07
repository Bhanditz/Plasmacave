#ifndef CAVE_HPP
#define CAVE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <vector>

#include "Node.hpp"

#define MAP_MAX_SIZE 10

Uint32 min(Uint32 a, Uint32 b) { return a<b?a:b; }
Uint32 max(Uint32 a, Uint32 b) { return a>b?a:b; }

class Cave {
 private:
    Node nodes[MAP_MAX_SIZE][MAP_MAX_SIZE][MAP_MAX_SIZE];
    GLuint face;
 public:
    const Uint32 width, height, depth; //voipi olla public, koska const ja konstruktori vaatii

    Cave(Uint32 s = MAP_MAX_SIZE) : width(min(s, MAP_MAX_SIZE)), height(min(s, MAP_MAX_SIZE)), depth(min(s, MAP_MAX_SIZE)) {
        Cave(s, s, s);
    }

    Cave(Uint32 w, Uint32 h, Uint32 d = MAP_MAX_SIZE) : width(min(w, MAP_MAX_SIZE)), height(min(h, MAP_MAX_SIZE)), depth(min(d, MAP_MAX_SIZE)) {
        for(Uint32 z = 0; z < d; z++) {
            for(Uint32 y = 0; y < h; y++) {
                for(Uint32 x = 0; x < w; x++) {
                    Node tmp = Node();
                    tmp.hit = rand()%2;
                    if ((x+y+z)%2) { tmp.setColor(1.0, 0.0, 0.0);
                    } else {         tmp.setColor(1.0, 1.0, 1.0); }
                    tmp.updateFace();

                    this->nodes[z][y][x] = tmp;
                }
            }
        }
    }

    void draw() {
//        glTranslated( -this->width/2.0, 0.0, -this->depth/2.0 );

        double xx;
        double zz;

        for(Uint32 z = 0; z < this->depth; z++) {
            for(Uint32 y = 0; y < this->height; y++) {
                for(Uint32 x = 0; x < this->width; x++) {
//                    if (!this->nodes[z][y][x].hit) continue;

                    xx = x-((double)this->width/2.0);
                    zz = z-((double)this->depth/2.0);

                    glTranslated(xx, -1.30, zz);
                    this->nodes[z][y][x].draw();
                    glTranslated(-xx, 1.30, -zz);
    /*                glBegin(GL_QUADS);
                        glVertex3d(xx-0.5, -1.30, zz-0.5);
                        glVertex3d(xx+0.5, -1.30, zz-0.5);
                        glVertex3d(xx+0.5, -1.30, zz+0.5);
                        glVertex3d(xx-0.5, -1.30, zz+0.5);
                    glEnd();*/
                }
            }
        }
    }

    bool isHitting(vec3 vec) {
        int x = floor(vec.x+0.5);
        if (x<0 || x>=(int)this->width)  return false;
        int y = floor(vec.y+0.5);
        if (y<0 || y>=(int)this->height) return false;
        int z = floor(vec.z+0.5);
        if (z<0 || z>=(int)this->depth)  return false;
        return this->nodes[z][y][x].hit;
    }
};

#endif
