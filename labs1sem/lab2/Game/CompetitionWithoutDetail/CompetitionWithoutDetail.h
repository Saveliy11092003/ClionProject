//
// Created by user on 08.11.22.
//
#include "../GameMatrix/GameMatrix.h"
#include<memory>
#include <iostream>
#include"../InterfaceGame/InterfaceGame.h"

using namespace std;

#ifndef LAB2_COMPETITIONWITHOUTDETAIL_H
#define LAB2_COMPETITIONWITHOUTDETAIL_H
#include "../GameStrategy.h"
#include "../StrategyFactory/StrategyFactory.h"

using namespace std;

enum StatusResult{
    WIN_ONE_FIRST,
    WIN_ONE_SECOND,
    WIN_ONE_THIRD,
    WIN_TWO_FIRST_SECOND,
    WIN_TWO_FIRST_THIRD,
    WIN_TWO_THIRD_SECOND,
    DRAW
};

class CompetitionWithoutDetail: public InterfaceGame {
private:
    int Steps;
    shared_ptr<GameStrategy> Strategy1;
    shared_ptr<GameStrategy> Strategy2;
    shared_ptr<GameStrategy> Strategy3;
    StatusResult DeterminationOfWinner(int a, int b, int c);
    void PrintResult(StatusResult);
public:
    CompetitionWithoutDetail(vector<shared_ptr<GameStrategy>> VectorStrategies, int a);
    void GetResult(GameMatrix Matrix) override;
};


#endif //LAB2_COMPETITIONWITHOUTDETAIL_H
