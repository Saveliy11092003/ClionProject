//
// Created by user on 28.10.22.
//

#ifndef LAB2_GAMEMATRIX_H
#define LAB2_GAMEMATRIX_H

#include<iostream>
#include<vector>
#include "../Choice.h"
#include "GameScore.h"
#include<fstream>
#include<memory>

using namespace std;

class GameMatrix {
public:
    GameMatrix();
    GameMatrix(string strMatrix);
    GameScore getScore(Choice a, Choice b, Choice c);

    ~GameMatrix();
private:
    void GetDigits(string str);
    vector<GameScore> Scores;
};

#endif //LAB2_GAMEMATRIX_H
