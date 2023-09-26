//
// Created by user on 17.11.22.
//

#ifndef LAB2_RANDOMSTRATEGY_H
#define LAB2_RANDOMSTRATEGY_H

#include <iostream>
#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>
#include <ctime>

using namespace std;


class RandomStrategy: public GameStrategy {
public:

    RandomStrategy(string File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~RandomStrategy() override = default;
private:
    ifstream ConfigFile;
};



#endif //LAB2_RANDOMSTRATEGY_H
