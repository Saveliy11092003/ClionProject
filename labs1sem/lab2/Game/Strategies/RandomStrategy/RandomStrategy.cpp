//
// Created by user on 17.11.22.
//

#include "RandomStrategy.h"

RandomStrategy::RandomStrategy(string NameFile, GameMatrix gameMatrix) {
}

Choice RandomStrategy::vote() {
    string PercentDefect;
    ConfigFile.open("/home/user/CLionProjects/lab2/Game/ConfigFiles/Random.txt");
    ConfigFile >> PercentDefect;
    ConfigFile.close();
    srand(time(NULL));
    int a = rand() % 100;
    int PercentDefectDigit;
    PercentDefectDigit = stoi(PercentDefect);
    if(a <= PercentDefectDigit){
        return DEFECT;
    }
    else{
      return COOPERATE;
    }
}

void RandomStrategy::update(Choice A, Choice B) {

}
