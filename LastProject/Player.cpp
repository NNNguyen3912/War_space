#include "Player.h"
#include "Constants.h"
#include <math.h>

player::player() : thrust(false) {
    name = "player";
}

void player::update() {
    if (thrust) {
        dx += cos(angle * DEGTORAD) * 0.1;
        dy += sin(angle * DEGTORAD) * 0.1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        dx -= cos(angle * DEGTORAD) * 0.1;
        dy -= sin(angle * DEGTORAD) * 0.1;
    }
    else {
        dx *= 0.99;
        dy *= 0.99;
    }

    int maxSpeed = 15;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x = W / 2;  
    y = H / 2;  
}


