#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity();
    virtual ~Entity();
    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update();
    void draw(sf::RenderWindow& app);
};

#endif // ENTITY_H
