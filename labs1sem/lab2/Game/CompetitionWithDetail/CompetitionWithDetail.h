//
// Created by user on 11.11.22.
//
#include "../CompetitionWithoutDetail/CompetitionWithoutDetail.h"
#ifndef LAB2_COMPETITIONWITHDETAIL_H
#define LAB2_COMPETITIONWITHDETAIL_H

#include "../GameStrategy.h"
#include "../StrategyFactory/StrategyFactory.h"
#include "Button.h"
#include <iostream>
#include"../InterfaceGame/InterfaceGame.h"

using namespace std;

enum StatusResultDetail{
    WIN_ONE_FIRST_DETAIL,
    WIN_ONE_SECOND_DETAIL,
    WIN_ONE_THIRD_DETAIL,
    WIN_TWO_FIRST_SECOND_DETAIL,
    WIN_TWO_FIRST_THIRD_DETAIL,
    WIN_TWO_THIRD_SECOND_DETAIL,
    DRAW_DETAIL
};

class CompetitionWithDetail: public  InterfaceGame{
    shared_ptr<GameStrategy> Strategy1;
    shared_ptr<GameStrategy> Strategy2;
    shared_ptr<GameStrategy> Strategy3;
    StatusResultDetail DeterminationOfWinner(int a, int b, int c);
    void PrintResult(StatusResultDetail);
public:
    CompetitionWithDetail(vector<shared_ptr<GameStrategy>> VectorStrategies);
    void GetResult(GameMatrix Matrix) override;
private:
    void PrintVote(Choice a);
};


#endif //LAB2_COMPETITIONWITHDETAIL_H
