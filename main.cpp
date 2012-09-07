#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>

#define DEBUG(str) debug(str, __LINE__);

#define SCREEN_WIDTH	1000
#define SCREEN_HEIGHT	700
#define SCREEN_WIDTH2	SCREEN_WIDTH/2.0
#define SCREEN_HEIGHT2	SCREEN_HEIGHT/2.0
#define SCREEN_D        ((double)SCREEN_HEIGHT/(double)SCREEN_WIDTH)
#define SCREEN_BPP		32
#define PI				3.1415926535

#include "Common.hpp"
#include "ControlHandler.hpp"
#include "Light.hpp"

namespace fps {
    double  fps;
    double  bb = 0.0, lbb = 0;
    double  tt = 0.0, ltt = 0;
    double  lr;
    int     fpslimit;
    double  numms;
    double  fpstxtd;
    char    fpstxt[256];
    bool    secondEvent;
    void regulate() {
        bb = SDL_GetTicks();
        double timeDiff = bb - lbb;

        if ( timeDiff < numms ) SDL_Delay( numms - timeDiff );
//        else valita!
        tt++;
        fps = 1000.0 * (tt-ltt) / timeDiff;
        ltt = tt;
        lbb = bb;

        if(bb-1000 > fpstxtd) {
            sprintf(fpstxt, "%.2f", fps);
            SDL_WM_SetCaption(fpstxt, NULL);
            fpstxtd = bb;
            secondEvent = true;
        } else {
            secondEvent = false;
        }
    }
    void setLimit(int _fpslimit) {
        fpslimit = _fpslimit;
        numms = 1000.0/(double)_fpslimit;
        fpstxtd = bb = SDL_GetTicks();
    }
}

void debug(const char* str, int line = -1) {
    if (line == -1) {
        printf("%i: DEBUG: %s\n", SDL_GetTicks(), str);
    } else {
        printf("%i: DEBUG(%i): %s\n", SDL_GetTicks(), line, str);
    }
};

void Quit(int returnCode = 0) {
	SDL_Quit();
	exit(returnCode);
};

SDL_Surface *surface;
Uint32 tt = 0, bb = 0;
int videoFlags, done = 0;
ControlHandler ctrl;
const SDL_VideoInfo *videoInfo;

float usXp = 0.0f;
float usYp = 0.0f;
float usZp = 0.0f;
float usMove = 1.0f;

std::vector<Light> lights;

GLuint LoadTexture(char*,int*,int*);
double sina(double a) { return sin(a/180.0f*PI); }
double cosa(double a) { return cos(a/180.0f*PI); }

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
    { return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2) + pow(z1-z2, 2)); }

float distance(float x1, float y1, float x2, float y2)
    { return distance(x1, y1, 0.0f, x2, y2, 0.0f); }

double s2wX(double x) { return (x-(SCREEN_WIDTH/(2.0)))/(SCREEN_WIDTH/(2.0)); }
double s2wY(double y) { return -(y-(SCREEN_WIDTH/(2.0*SCREEN_D)))/(SCREEN_WIDTH/(2.0*SCREEN_D)); }
//float viewpointToScreenX(float x) { return (x+1.0)*SCREEN_WIDTH/2.0; }
//float viewpointToScreenY(float y) { return SCREEN_HEIGHT * (y+SCREEN_D)/(2*SCREEN_D); }

#include "Engine.hpp"

int main( int argc, char **argv ) {
    debug("STARTING", __LINE__);

    printf("\tSDL(major) v.%i\n", SDL_MAJOR_VERSION);
    printf("\tSDL(minor) v.%i\n", SDL_MINOR_VERSION);
    printf("\tSDL(patch) v.%i\n", SDL_PATCHLEVEL);
    printf("\tSDL_mixer(major) v.%i\n", SDL_MIXER_MAJOR_VERSION);
    printf("\tSDL_mixer(minor) v.%i\n", SDL_MIXER_MINOR_VERSION);
    printf("\tSDL_mixer(patch) v.%i\n", SDL_MIXER_PATCHLEVEL);
    printf("\tSDL_image(major) v.%i\n", SDL_IMAGE_MAJOR_VERSION);
    printf("\tSDL_image(minor) v.%i\n", SDL_IMAGE_MINOR_VERSION);
    printf("\tSDL_image(patch) v.%i\n", SDL_IMAGE_PATCHLEVEL);
    printf("\tOPENGL v.%i\n", GL_VERSION);

    debug("INITIALIZING VARIABLES", __LINE__);
//    Light tmplight = Light(GL_LIGHT1);
//    tmplight.setPosition(4.0f, 4.0f, 4.0f );
//    tmplight.setAmbient( 0.5f, 0.5f, 0.5f );
//    tmplight.setDiffuse( 1.0f, 1.0f, 1.0f );

//    lights.push_back(tmplight);

    Engine *game = new Engine();
//    fps::setLimit(60);

    debug("INITIALIZING SDL", __LINE__);
    debug("Initing SDL(video)", __LINE__);
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
		Quit(1);
	}
	if (!(videoInfo = SDL_GetVideoInfo())) {
		fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
		Quit(1);
	}

	videoFlags  = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	videoFlags |= SDL_RESIZABLE;
    videoFlags |= (videoInfo->hw_available)?SDL_HWSURFACE:SDL_SWSURFACE;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

    debug("Creating surface", __LINE__);
	if (!(surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, videoFlags ))) {
		fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
		Quit(1);
	}
	SDL_ShowCursor(0);
    SDL_WarpMouse(SCREEN_WIDTH2, SCREEN_HEIGHT2);

// --------- INITIALIZING OGL ---------

    debug("INITIALIZING OPENGL", __LINE__);
//    glEnable( GL_TEXTURE_2D );
//	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthMask(GL_TRUE);
//	glEnable(GL_LIGHTING);
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

/*    for(Uint32 i = 0; i < lights.size(); i++) {
        glLightfv(lights[i].getId(), GL_AMBIENT,  lights[i].getAmbient());
        glLightfv(lights[i].getId(), GL_DIFFUSE,  lights[i].getDiffuse());
        glLightfv(lights[i].getId(), GL_POSITION, lights[i].getPosition());
        glEnable (lights[i].getId());
    }*/

/*    glLightfv(GL_LIGHT1, GL_AMBIENT,  { 0.5f, 0.5f, 0.5f, 1.0f });
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  { 1.0f, 1.0f, 1.0f, 1.0f });
    glLightfv(GL_LIGHT1, GL_POSITION, { 4.0f, 4.0f, 4.0f, 1.0f });
    glEnable (GL_LIGHT1);*/

	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -(double)SCREEN_HEIGHT/(double)SCREEN_WIDTH, (double)SCREEN_HEIGHT/(double)SCREEN_WIDTH, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    debug("INITIALIZING GLEW", __LINE__);

    switch(GLenum err = glewInit()) {
        case GLEW_OK: break;
        default:
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    debug("LOADING", __LINE__);

    debug("MAPINFO:", __LINE__);
    printf("Cave: (%i,%i,%i)\n", game->getMap()->width, game->getMap()->height, game->getMap()->depth);

    debug("STARTING THE LOOP", __LINE__);

	while (!done) {
        ctrl.update();
        fps::regulate();
        SDL_WarpMouse(SCREEN_WIDTH2, SCREEN_HEIGHT2);

        if (ctrl.keyDown(SDLK_d) || ctrl.keyDown(SDLK_RIGHT)) game->getPlayer()->turn( 0.0, 10.0, 0.0);
        if (ctrl.keyDown(SDLK_a) || ctrl.keyDown(SDLK_LEFT))  game->getPlayer()->turn( 0.0,-10.0, 0.0);
        if (ctrl.keyDown(SDLK_w) || ctrl.keyDown(SDLK_UP))    game->getPlayer()->move(  1.0 );
        if (ctrl.keyDown(SDLK_s) || ctrl.keyDown(SDLK_DOWN))  game->getPlayer()->move( -1.0 );
        if (ctrl.keyHit(SDLK_SPACE)) game->getPlayer()->jump( 1.0 );
        if (ctrl.keyHit(SDLK_ESCAPE)) done = 1;
        if (ctrl.keyHit(SDLK_RETURN)) {
            if (game->isRunning()) game->stop();
            else                   game->run();
        }

        game->getPlayer()->turn( 0.0, (ctrl.mouseX()-SCREEN_WIDTH2)/10.0, 0.0);
        game->getPlayer()->turn( (ctrl.mouseY()-SCREEN_HEIGHT2)/10.0, 0.0, 0.0);


        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();

        glRotated(game->getPlayer()->rotate.x, 1, 0, 0);
        glRotated(game->getPlayer()->rotate.y, 0, 1, 0);
        glRotated(game->getPlayer()->rotate.z, 0, 0, 1);

        glTranslated(game->getPlayer()->pos.x, game->getPlayer()->pos.y, game->getPlayer()->pos.z);

        glBegin(GL_LINES);
            glColor3d( 1.0, 1.0, 1.0 );
            glVertex3d( 10.0, 0.0, 0.0 );
            glVertex3d( -10.0, 0.0, 0.0 );

            glVertex3d( 0.0, 10.0, 0.0 );
            glVertex3d( 0.0,-10.0, 0.0 );

            glVertex3d( 0.0, 0.0, 10.0 );
            glVertex3d( 0.0, 0.0,-10.0 );
        glEnd();

        game->update();
        game->draw();

        SDL_GL_SwapBuffers( );
	}
	Quit(0);
	return 0;
}
