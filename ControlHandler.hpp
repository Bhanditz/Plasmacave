#ifndef CONTROLHANDLER_HPP
#define CONTROLHANDLER_HPP

#include <map>
#include <SDL/SDL.h>

class ControlHandler {
 private:
    SDL_Event _event;
    std::map<Uint8, SDL_Event> _events;

    int mx, my, mp, lmx, lmy;

    std::map<SDLKey, bool> _keyDown;
    std::map<SDLKey, bool> _keyHit;
    std::map<SDLKey, bool> _keyUp;

 public:
    ControlHandler() {
        update();
    }

    void update() {
        _keyUp.clear();
        _keyHit.clear();
        _events.clear();

		lmx = mx;     lmy = my;
		mp = SDL_GetMouseState(&mx, &my);

		while ( SDL_PollEvent( &_event ) ) {
            switch(_event.type) {
                case SDL_KEYDOWN:
                    _keyDown[_event.key.keysym.sym] = true;
                    _keyHit[_event.key.keysym.sym] = true;
                    break;
                case SDL_KEYUP:
                    _keyDown[_event.key.keysym.sym] = false;
                    _keyUp[_event.key.keysym.sym] = true;
                    break;
                default:
                    this->_events[_event.type] = _event;
            }
		}
    }
    bool keyDown(SDLKey key) { return this->_keyDown[key]; }
    bool keyHit(SDLKey key)  { return this->_keyHit[key]; }
    bool keyUp(SDLKey key)   { return this->_keyUp[key]; }

    int mouseX()   { return this->mx; }
    int mouseY()   { return this->my; }
    int mouseXP()   { return this->lmx-this->mx; }
    int mouseYP()   { return this->lmy-this->my; }
    int mouseP()   { return this->mp; }

    std::map<Uint8, SDL_Event> getEvents() { return this->_events; }
    SDL_Event getEvent(Uint8 key) { return this->_events[key]; }
};

#endif
