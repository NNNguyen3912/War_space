#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int points; 

public:
 
    Score();

    void increase(int value);

    int getPoints() const;

    void reset();
};

#endif
