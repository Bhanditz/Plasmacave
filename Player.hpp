#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include "Character.hpp"

class Player : public Character {
 private:
    char *name;
 public:
    Player() : Character() {}
};
#endif
