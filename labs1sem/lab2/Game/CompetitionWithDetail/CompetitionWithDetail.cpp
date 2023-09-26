//
// Created by user on 11.11.22.
//

#include "CompetitionWithDetail.h"

void CompetitionWithDetail::GetResult(GameMatrix Matrix) {
    int SumStrategy1 = 0;
    int SumStrategy2 = 0;
    int SumStrategy3 = 0;
    int count = 1;
    while(true){
        string StatusButtonNow;
        getline(cin, StatusButtonNow);
        Button ControlButton;
        if(ControlButton.CheckStatusButton(StatusButtonNow) == Stop){
            break;
        }

        Choice ChoiceFirst = Strategy1->vote();
        Choice ChoiceSecond = Strategy2->vote();
        Choice ChoiceThird = Strategy3->vote();
        GameScore Score = Matrix.getScore(ChoiceFirst,ChoiceSecond,ChoiceThird);

        int ScoreFirstStrategyStep = Score.getScoreA();
        int ScoreSecondStrategyStep = Score.getScoreB();
        int ScoreThirdStrategyStep= Score.getScoreC();

        SumStrategy1 += ScoreFirstStrategyStep;
        SumStrategy2 += ScoreSecondStrategyStep;
        SumStrategy3 += ScoreThirdStrategyStep;

        cout << "Turn " << count << endl;
        count += 1;

        cout << "Choice of First strategy "; PrintVote(ChoiceFirst);
        cout << "Choice of Second strategy "; PrintVote(ChoiceSecond);
        cout << "Choice of Third strategy "; PrintVote(ChoiceThird); cout << endl;

        cout << "First strategy score per turn " << ScoreFirstStrategyStep << endl;
        cout << "Second strategy score per turn " << ScoreSecondStrategyStep << endl;
        cout << "Third strategy score per turn " << ScoreThirdStrategyStep << endl << endl;

        cout << "Sum of score of First Strategy " << SumStrategy1 << endl;
        cout << "Sum of score of Second Strategy " << SumStrategy2 << endl;
        cout << "Sum of score of Third Strategy " << SumStrategy3 << endl;
        Strategy1->update(ChoiceSecond, ChoiceThird);
        Strategy2->update(ChoiceFirst, ChoiceThird);
        Strategy3->update(ChoiceSecond, ChoiceFirst);
    }
    StatusResultDetail Status = DeterminationOfWinner(SumStrategy1, SumStrategy2, SumStrategy3);
    PrintResult(Status);
}


StatusResultDetail CompetitionWithDetail::DeterminationOfWinner(int a, int b, int c){
    if ((a>b) && (a>c)){
        return WIN_ONE_FIRST_DETAIL;
    }
    if ((b>a) && (b>c)){
        return WIN_ONE_SECOND_DETAIL;
    }
    if ((c>b) && (c>a)){
        return WIN_ONE_THIRD_DETAIL;
    }
    if((a=b) && (a>c)){
        return WIN_TWO_FIRST_SECOND_DETAIL;
    }
    if((a=c) && (a>b)){
        return WIN_TWO_FIRST_THIRD_DETAIL;
    }
    if((c=b) && (c>a)){
        return WIN_TWO_THIRD_SECOND_DETAIL;
    }
    if((a=b) && (a=c)){
        return DRAW_DETAIL;
    }
}

void CompetitionWithDetail::PrintResult(StatusResultDetail Status) {
    switch (Status) {
        case WIN_ONE_FIRST_DETAIL:
            std::cout << "First strategy wins" << std::endl;
            return;
        case WIN_ONE_SECOND_DETAIL:
            std::cout << "Second strategy wins" << std::endl;
            return;
        case WIN_ONE_THIRD_DETAIL:
            std::cout << "Third strategy wins" << std::endl;
            return;
        case WIN_TWO_FIRST_SECOND_DETAIL:
            std::cout << "First and Second strategies win" << std::endl;
            return;
        case WIN_TWO_FIRST_THIRD_DETAIL:
            std::cout << "First and Third strategies win" << std::endl;
            return;
        case WIN_TWO_THIRD_SECOND_DETAIL:
            std::cout << "Second and Third strategies win" << std::endl;
            return;
        case DRAW_DETAIL:
            std::cout << "Draw" << std::endl;
            return;
    }
}

CompetitionWithDetail::CompetitionWithDetail(vector<shared_ptr<GameStrategy>> VectorStrategies) {
    StrategyFactory Factory;
    //int i = VectorStrategies.size();
    Strategy1 = VectorStrategies[0];
    Strategy2 = VectorStrategies[1];
    Strategy3 = VectorStrategies[2];
}


void CompetitionWithDetail::PrintVote(Choice a) {
    if(a == DEFECT){
        cout << "Defect" << endl;
    }else{
        cout << "COOPERATE" << endl;
    }
}
