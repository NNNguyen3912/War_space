#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class bullet : public Entity {
public:
    bullet();
    void update() override;
};

#endif // BULLET_H
