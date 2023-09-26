//
// Created by user on 28.10.22.
//

#ifndef LAB2_GAMESTRATEGY_H
#define LAB2_GAMESTRATEGY_H

#include "Choice.h"

enum StrategyName {
    ALWAYS_CHOICE_C,
    ALWAYS_CHOICE_D,
    ALTERNATING,
    TIT_FOT_TAT_SOFT,
    TIT_FOT_TAT_HARD,
    RANDOM
};

class GameStrategy {
public:

    virtual Choice vote() = 0;

    virtual void update(Choice playerA, Choice playerB) = 0;

    virtual ~GameStrategy() = default;

};

#endif //LAB2_GAMESTRATEGY_H
