#ifndef COMMON_HPP
#define COMMON_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>


struct vec3 {
    double x, y, z;
    vec3( double _x=0.0, double _y=0.0, double _z=0.0 ) : x(_x), y(_y), z(_z) {};
    void clear() { x = 0.0; y = 0.0; z = 0.0; };
};

struct vec2 {
    double x, y;
    vec2( double _x=0.0, double _y=0.0 ) : x(_x), y(_y) {};
    void clear() { x = 0.0; y = 0.0; };
};

void glColor3(vec3 clr) { glColor3d(clr.x, clr.y, clr.z); }

void drawCube(GLfloat w, GLfloat h, GLfloat d) {
    w = w/2;
    h = h/2;
    d = d/2;
    glBegin( GL_QUADS );
        //takaneliö
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h, -d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h, -d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h, -d); // oikea ylä

        //etuneliö
        glNormal3f(0.0f, 0.0f,  1.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h,  d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h,  d); // oikea ylä

        //vasen neliö
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f(-w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f(-w,  h, -d); // oikea ylä

        //oikea neliö
        glNormal3f( 1.0f,  0.0f, 0.0f);
        glTexCoord2i( 0, 1 ); glVertex3f( w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f( w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w,  h, -d); // oikea ylä

        //yläneliö
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w, -h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h, -d); // oikea ylä

        //alaneliö
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w,  h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w,  h, -d); // oikea ylä
    glEnd();

#if false
    glColor3f(0,0,0);
    glBegin( GL_LINE_LOOP );
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h, -d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h, -d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h, -d); // oikea ylä
    glEnd();
    glBegin( GL_LINE_LOOP );
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h,  d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h,  d); // oikea ylä
    glEnd();
    glBegin( GL_LINE_LOOP );
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f(-w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f(-w,  h, -d); // oikea ylä
    glEnd();
    glBegin( GL_LINE_LOOP );
        glTexCoord2i( 0, 1 ); glVertex3f( w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f( w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w,  h, -d); // oikea ylä
    glEnd();
    glBegin( GL_LINE_LOOP );
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2i( 0, 1 ); glVertex3f(-w, -h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w, -h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w, -h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w, -h, -d); // oikea ylä
    glEnd();
    glBegin( GL_LINE_LOOP );
        glTexCoord2i( 0, 1 ); glVertex3f(-w,  h, -d); // vasen ylä
        glTexCoord2i( 0, 0 ); glVertex3f(-w,  h,  d); // vasen ala
        glTexCoord2i( 1, 0 ); glVertex3f( w,  h,  d); // oikea ala
        glTexCoord2i( 1, 1 ); glVertex3f( w,  h, -d); // oikea ylä
    glEnd();
#endif
}

void drawCube(GLdouble w, GLdouble h, GLdouble d)
    { drawCube((GLfloat)w, (GLfloat)h, (GLfloat)d); }

void drawCube(GLfloat s)
    { drawCube(s, s, s); }

void drawCube(GLdouble s)
    { drawCube((GLfloat)s); }



//http://sdl.beuc.net/sdl.wiki/OpenGL_Texture_Example
GLuint LoadTexture(char *filename,int *textw,int *texth) {
        GLuint textureid;
        int mode;

        SDL_Surface *surface = IMG_Load(filename);

        if (!surface)  return 0;

        if (surface->format->BytesPerPixel == 3)      mode = GL_RGB;
        else if (surface->format->BytesPerPixel == 4) mode = GL_RGBA;
        else {
                SDL_FreeSurface(surface);
                return 0;
        }

        *textw = surface->w;
        *texth = surface->h;

        glGenTextures(1, &textureid);
        glBindTexture(GL_TEXTURE_2D, textureid);
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        SDL_FreeSurface(surface);
        return textureid;
}

#endif

