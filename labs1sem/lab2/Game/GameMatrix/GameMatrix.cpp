//
// Created by user on 28.10.22.
//

#include "GameMatrix.h"


GameScore GameMatrix::getScore(Choice a, Choice b, Choice c) {
    GameScore result;
    if(a == COOPERATE && b == COOPERATE && c == COOPERATE ) {
        return (Scores[0]);
    }
    if(a == COOPERATE && b == COOPERATE && c == DEFECT ) {
        return (Scores[1]);
    }
    if(a == COOPERATE && b == DEFECT && c == COOPERATE ) {
        return (Scores[2]);
    }
    if(a == DEFECT && b == COOPERATE && c == COOPERATE ) {
        return (Scores[3]);
    }
    if(a == COOPERATE && b == DEFECT && c == DEFECT ) {
        return (Scores[4]);
    }
    if(a == DEFECT && b == COOPERATE && c == DEFECT ) {
        return (Scores[5]);
    }
    if(a == DEFECT && b == DEFECT && c == COOPERATE ) {
        return (Scores[6]);
    }
    if(a == DEFECT && b == DEFECT && c == DEFECT ) {
        return (Scores[7]);
    }
    return result;
}


GameMatrix::GameMatrix() {
    GameScore result;
    result.setScoreA(7);
    result.setScoreB(7);
    result.setScoreC(7);
    Scores.push_back(result);

    result.setScoreA(3);
    result.setScoreB(3);
    result.setScoreC(9);
    Scores.push_back(result);

    result.setScoreA(3);
    result.setScoreB(9);
    result.setScoreC(3);
    Scores.push_back(result);


    result.setScoreA(9);
    result.setScoreB(3);
    result.setScoreC(3);
    Scores.push_back(result);


    result.setScoreA(0);
    result.setScoreB(5);
    result.setScoreC(5);
    Scores.push_back(result);

    result.setScoreA(5);
    result.setScoreB(0);
    result.setScoreC(5);
    Scores.push_back(result);

    result.setScoreA(5);
    result.setScoreB(5);
    result.setScoreC(0);
    Scores.push_back(result);


    result.setScoreA(1);
    result.setScoreB(1);
    result.setScoreC(1);
    Scores.push_back(result);
}

GameMatrix::GameMatrix(string StrMatrix) {
    ifstream File;
    try{
        File.open(StrMatrix);
        if(File.fail()){
            throw StrMatrix;
        }
    }
    catch (string e){
        cout << e << "was not successfully opened" << endl;
    }
    string str;
    int j=0;
    GameScore result;
    if(!File.is_open()){
        cout << "File open error" << endl;
    }
    else{
        vector<string> VectorStrMatrix;
        int i=0;
        while(!File.eof()){
            getline(File,str);
            VectorStrMatrix.push_back(str);
            str = "";
            i++;
        }

        for(int k=0;k<VectorStrMatrix.size();k++){
            int v=0;
            string strDigit;
            int count = 1;
            v=0;
            while(VectorStrMatrix[k][v] != '\n' && VectorStrMatrix[k][v] != '\0' ){
                while(VectorStrMatrix[k][v] != ' ' && VectorStrMatrix[k][v] != '\n' && VectorStrMatrix[k][v] != '\0'){
                    if(VectorStrMatrix[k][v] >= '0' && VectorStrMatrix[k][v] <= '9'){
                        strDigit.push_back(VectorStrMatrix[k][v]);
                    }
                    v++;
                }
                if (count == 1){
                    result.setScoreA(stoi(strDigit));
                    v++;
                }
                if (count == 2){
                    result.setScoreB(stoi(strDigit));
                    v++;
                }
                if (count == 3){
                    result.setScoreC(stoi(strDigit));
                    Scores.push_back(result);
                    count = 1;
                    j++;
                }
                count++;
                strDigit = "";
            }
        }
    }

}


GameMatrix::~GameMatrix() {
}


