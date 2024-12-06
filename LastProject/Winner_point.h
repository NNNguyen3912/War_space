#ifndef WINNER_POINT_H
#define WINNER_POINT_H

#include "Entity.h"

class WinnerPoint : public Entity {
public:
    WinnerPoint();

    void update() override;
};
#endif
