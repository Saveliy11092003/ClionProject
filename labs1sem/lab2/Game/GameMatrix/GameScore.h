//
// Created by user on 08.11.22.
//

#ifndef LAB2_GAMESCORE_H
#define LAB2_GAMESCORE_H


class GameScore {

public:

    void setScoreA(int score);

    void setScoreB(int score);

    void setScoreC(int score);

    int getScoreA() const;

    int getScoreB() const;

    int getScoreC() const;

private:
    int scoreA;
    int scoreB;
    int scoreC;

};


#endif //LAB2_GAMESCORE_H
