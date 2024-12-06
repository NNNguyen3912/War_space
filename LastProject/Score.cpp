#include "Score.h"

Score::Score() : points(0) {}

void Score::increase(int value) {
    points += value;
}

int Score::getPoints() const {
    return points;
}

void Score::reset() {
    points = 0;
}
