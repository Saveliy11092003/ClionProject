//
// Created by user on 17.11.22.
//

#ifndef LAB2_TITFORTATHARD_H
#define LAB2_TITFORTATHARD_H

#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>

using namespace std;


class TitForTatHard: public GameStrategy {
public:

    TitForTatHard(string File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~TitForTatHard() override = default;
private:
    Choice PreviousTurnFirstOpponent = COOPERATE;
    Choice PreviousTurnSecondOpponent = COOPERATE;
};


#endif //LAB2_TITFORTATHARD_H
