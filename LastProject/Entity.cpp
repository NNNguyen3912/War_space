#include "Entity.h"

Entity::Entity() : x(0), y(0), dx(0), dy(0), R(0), angle(0), life(true) {}

Entity::~Entity() {}

void Entity::settings(Animation& a, int X, int Y, float Angle, int radius) {
    anim = a;
    x = X; y = Y;
    angle = Angle;
    R = radius;
}

void Entity::update() {}

void Entity::draw(sf::RenderWindow& app) {
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    app.draw(anim.sprite);
}
