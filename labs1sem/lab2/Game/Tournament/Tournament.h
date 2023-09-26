//
// Created by user on 11.11.22.
//
#include<iostream>
#include "../GameStrategy.h"
#include<vector>
#include<string.h>
#include <string>
#include <limits.h>
#include "../GameMatrix/GameMatrix.h"
#include "../StrategyFactory/StrategyFactory.h"
#include<memory>
#include"../InterfaceGame/InterfaceGame.h"

#ifndef LAB2_TOURNAMENT_H
#define LAB2_TOURNAMENT_H
using namespace std;

class Tournament : public InterfaceGame{
private:
    vector<shared_ptr<GameStrategy>> VectorStrategies;
    int Steps;
    void PrintVote(Choice a);
    void PrintAllTurns(GameMatrix Matrix, shared_ptr<vector<int>> SumsVector);
    int Max(shared_ptr<vector<int>> SumsVector);
    void PrintResult(shared_ptr<vector<int>> SumsVectors);
    void SumsUpdate(vector<shared_ptr<GameStrategy>> VectorStrategies, shared_ptr<vector<int>> VectorSums, int i, int j, int k, GameMatrix matrix);
public:
    Tournament(vector<shared_ptr<GameStrategy>>, int n);
    void GetResult(GameMatrix Matrix) override;
};


#endif //LAB2_TOURNAMENT_H
