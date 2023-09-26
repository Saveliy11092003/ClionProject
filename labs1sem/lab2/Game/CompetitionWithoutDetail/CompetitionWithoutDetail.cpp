//
// Created by user on 08.11.22.
//

#include "CompetitionWithoutDetail.h"

void CompetitionWithoutDetail::GetResult(GameMatrix Matrix) {
    int SumStrategy1 = 0;
    int SumStrategy2 = 0;
    int SumStrategy3 = 0;
    for(int i = 0; i < Steps; i++){

        Choice ChoiceFirst = Strategy1->vote();
        Choice ChoiceSecond = Strategy2->vote();
        Choice ChoiceThird = Strategy3->vote();

        GameScore Score = Matrix.getScore(ChoiceFirst,ChoiceSecond, ChoiceThird);

        SumStrategy1 += Score.getScoreA();
        SumStrategy2 += Score.getScoreB();
        SumStrategy3 += Score.getScoreC();

        Strategy1->update(ChoiceSecond, ChoiceThird);
        Strategy2->update(ChoiceFirst, ChoiceThird);
        Strategy3->update(ChoiceSecond, ChoiceFirst);
    }
    StatusResult Status = DeterminationOfWinner(SumStrategy1, SumStrategy2, SumStrategy3);
    PrintResult(Status);
}


StatusResult CompetitionWithoutDetail::DeterminationOfWinner(int a, int b, int c){
    if ((a>b) && (a>c)){
        return WIN_ONE_FIRST;
    }
    if ((b>a) && (b>c)){
        return WIN_ONE_SECOND;
    }
    if ((c>b) && (c>a)){
        return WIN_ONE_THIRD;
    }
    if((a=b) && (a>c)){
        return WIN_TWO_FIRST_SECOND;
    }
    if((a=c) && (a>b)){
        return WIN_TWO_FIRST_THIRD;
    }
    if((c=b) && (c>a)){
        return WIN_TWO_THIRD_SECOND;
    }
    if((a=b) && (a=c)){
        return DRAW;
    }
}

void CompetitionWithoutDetail::PrintResult(StatusResult Status) {
    switch (Status) {
        case WIN_ONE_FIRST:
            std::cout << "First strategy wins" << std::endl;
            return;
        case WIN_ONE_SECOND:
            std::cout << "Second strategy wins" << std::endl;
            return;
        case WIN_ONE_THIRD:
            std::cout << "Third strategy wins" << std::endl;
            return;
        case WIN_TWO_FIRST_SECOND:
            std::cout << "First and Second strategies win" << std::endl;
            return;
        case WIN_TWO_FIRST_THIRD:
            std::cout << "First and Third strategies win" << std::endl;
            return;
        case WIN_TWO_THIRD_SECOND:
            std::cout << "Second and Third strategies win" << std::endl;
            return;
        case DRAW:
            std::cout << "Draw" << std::endl;
            return;
    }
}

CompetitionWithoutDetail::CompetitionWithoutDetail(vector<shared_ptr<GameStrategy>> VectorStrategies, int a) {

    StrategyFactory Factory;
    Strategy1 = VectorStrategies[0];
    Strategy2 = VectorStrategies[1];
    Strategy3 = VectorStrategies[2];
    Steps = a;
}

