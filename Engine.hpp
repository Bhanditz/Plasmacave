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

    Cave   *getMap();
    Player *getPlayer();

    void run();
    void stop();
    bool isRunning();

    void update();

    void drawGUI();
    void draw();
};

Engine::Engine() : player(Player()) {
    this->player.setPos(0.0, 0.0, 0.0);
    this->player.setRotate(0.0, 20.0, 0.0);
    this->player.setSpeed(1.0, 0.0009);

    this->running = false;
    this->map = new Cave();
}

Cave   *Engine::getMap()    { return this->map; }
Player *Engine::getPlayer() { return &this->player; }

void Engine::run() {
    this->running = true;
    debug("Start to run!", __LINE__);
}
void Engine::stop() {
    this->running = false;
    debug("Running stopped!", __LINE__);
}
bool Engine::isRunning() { return this->running; }

void Engine::update() {
    if (!this->running) return;

    this->player.update();
    this->player.posp.y = 0.0;
}

void Engine::drawGUI() {

}
void Engine::draw() {
    this->getMap()->draw();
    drawGUI();
}

#endif

