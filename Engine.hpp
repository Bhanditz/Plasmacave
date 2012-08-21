#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <GL/glew.h>

#include "Cave.hpp"
#include "Player.hpp"

class Engine {
 private:
    Uint32  lastRun;
    Uint32  runDelay;
    bool    running;
    Player  player;
    Cave    *map;
 public:
    Engine();

    Cave *getMap();

    void run();
    void stop();
    bool isRunning();

    void update();

    void drawGUI();
    void draw();
};

Engine::Engine() : player(Player()) {
    this->running = false;
    this->lastRun = 0;
    this->runDelay = 250;
    this->map = new Cave();
}

Cave *Engine::getMap() { return this->map; }

void Engine::run() {
    this->running = true;
    this->lastRun = SDL_GetTicks();
    debug("Start to run!", __LINE__);
}
void Engine::stop() {
    this->running = false;
    debug("Running stopped!", __LINE__);
}
bool Engine::isRunning() { return this->running; }

void Engine::update() {
    if (!this->running) return;
    if (SDL_GetTicks() < this->lastRun + this->runDelay) return;

    //TODO

    this->lastRun = SDL_GetTicks();
}

void Engine::drawGUI() {

}
void Engine::draw() {
    this->getMap()->draw();
    drawGUI();
}

#endif

