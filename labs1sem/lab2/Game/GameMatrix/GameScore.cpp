//
// Created by user on 08.11.22.
//

#include "GameScore.h"


    void GameScore::setScoreA(int score) {
        this->scoreA = score;
    }

    void GameScore::setScoreB(int score) {
        this->scoreB = score;
    }

    void GameScore::setScoreC(int score) {
        this->scoreC = score;
    }

    int GameScore::getScoreA() const {
        return this->scoreA;
    }

    int GameScore::getScoreB() const {
        return this->scoreB;
    }

    int GameScore::getScoreC() const {
        return this->scoreC;
    }

