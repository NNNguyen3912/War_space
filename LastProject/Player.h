#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class player : public Entity {
public:
    bool thrust;

    player();
    void update() override;
};

#endif // PLAYER_H
