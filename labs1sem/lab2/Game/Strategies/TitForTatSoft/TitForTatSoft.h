//
// Created by user on 28.10.22.
//

#ifndef LAB2_TITFORTATSOFT_H
#define LAB2_TITFORTATSOFT_H

#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>

using namespace std;


class TitForTatSoft:public GameStrategy {
public:

    TitForTatSoft(string File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~TitForTatSoft() override = default;
private:
    Choice PreviousTurnFirstOpponent = COOPERATE;
    Choice PreviousTurnSecondOpponent = COOPERATE;
};


#endif //LAB2_TITFORTATSOFT_H
