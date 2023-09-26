//
// Created by user on 11.11.22.
//

#include "Tournament.h"

void Tournament::PrintResult(shared_ptr<vector<int>> SumsVector) {
    int ElementMax = Max(SumsVector);
    for(int i=0;i<SumsVector->size();i++){
        if(ElementMax == (*SumsVector)[i]){
            cout << i+1 << " Strategy wins" << endl;
        }
    }
}

Tournament::Tournament(vector<shared_ptr<GameStrategy>> VectorNames, int n) {
    StrategyFactory Factory;
    for(int i = 0; i < VectorNames.size(); i++){
        VectorStrategies.push_back(VectorNames[i]);
    }
    Steps = n;
}

void Tournament::GetResult(GameMatrix Matrix) {
    shared_ptr<vector<int>> SumsVectors = shared_ptr<vector<int>> (new vector<int>(VectorStrategies.size()));
    PrintAllTurns(Matrix, SumsVectors);
    PrintResult(SumsVectors);
}

void Tournament::SumsUpdate(vector<shared_ptr<GameStrategy>> VectorStrategies,
                            shared_ptr<vector<int>> VectorSums, int i, int j, int k, GameMatrix Matrix) {
    int v=0;
    if(v == i){
        v = i+1;
    }
    if(v == j){
        v = j+1;
    }
    if(v == k){
        v = k+1;
    }
    for(int l = 0; l < Steps; l++) {
        Choice ChoiceFirst = VectorStrategies[i]->vote();
        Choice ChoiceSecond = VectorStrategies[j]->vote();
        Choice ChoiceThird = VectorStrategies[k]->vote();
        GameScore Score = Matrix.getScore(ChoiceFirst, ChoiceSecond, ChoiceThird);

        int ScoreFirstStrategyStep = Score.getScoreA();
        int ScoreSecondStrategyStep = Score.getScoreB();
        int ScoreThirdStrategyStep = Score.getScoreC();

        (*VectorSums)[i] += ScoreFirstStrategyStep;
        (*VectorSums)[j] += ScoreSecondStrategyStep;
        (*VectorSums)[k] += ScoreThirdStrategyStep;


        cout << "Choice of " << i + 1 << " strategy ";
        PrintVote(ChoiceFirst);
        cout << "Choice of " << j + 1 << " strategy ";
        PrintVote(ChoiceSecond);
        cout << "Choice of " << k + 1 << " strategy ";
        PrintVote(ChoiceThird);
        cout << endl;

        cout << i + 1 << " strategy score per turn " << ScoreFirstStrategyStep << endl;
        cout << j + 1 << " strategy score per turn " << ScoreSecondStrategyStep << endl;
        cout << k + 1 << " strategy score per turn " << ScoreThirdStrategyStep << endl << endl;


        cout << "Sum of score of " << i + 1 << " Strategy " << (*VectorSums)[i] << endl;
        cout << "Sum of score of " << j + 1 << " Strategy " << (*VectorSums)[j] << endl;
        cout << "Sum of score of " << k + 1 << " Strategy " << (*VectorSums)[k] << endl;
        cout << "Sum of score of " << v + 1 << " Strategy " << (*VectorSums)[v] << endl << endl;

        VectorStrategies[i]->update(ChoiceSecond, ChoiceThird);
        VectorStrategies[j]->update(ChoiceFirst, ChoiceThird);
        VectorStrategies[k]->update(ChoiceSecond, ChoiceFirst);
    }
}

void Tournament::PrintVote(Choice a) {
    if(a == DEFECT){
        cout << "Defect" << endl;
    }else{
        cout << "COOPERATE" << endl;
    }
}

void Tournament::PrintAllTurns(GameMatrix Matrix, shared_ptr<vector<int>> SumsVectors) {
    int N = VectorStrategies.size();
    int count = 1;
    for(int i=0;i<N-2;i++){
        for(int j=i+1;j<N-1;j++){
            for(int k=j+1;k < N; k++){
                cout << "Competition " << count << endl;
                count++;
                SumsUpdate(VectorStrategies, SumsVectors, i, j, k, Matrix);
            }
        }
    }
}

int Tournament::Max(shared_ptr<vector<int>> SumsVector) {
    int ElementMax = INT_MIN;
    for(int i=0;i<SumsVector->size(); i++){
        if((*SumsVector)[i] > ElementMax){
            ElementMax = (*SumsVector)[i];
        }
    }
    return ElementMax;
}
