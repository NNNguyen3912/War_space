#include "Winner_point.h"
#include "Constants.h" 

WinnerPoint::WinnerPoint() {
    name = "winner_point";
    dx = (rand() % 100 - 50) / 100.0;
    dy = (rand() % 100 - 50) / 100.0; 
}

void WinnerPoint::update() {
    x += dx;
    y += dy;

    if (x > W) x = 0;
    if (x < 0) x = W;
    if (y > H) y = 0;
    if (y < 0) y = H;
}
