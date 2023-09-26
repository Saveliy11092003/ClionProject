//
// Created by user on 17.11.22.
//

#ifndef LAB2_ALTERNATINGVOTESTRATEGY_H
#define LAB2_ALTERNATINGVOTESTRATEGY_H

#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>

using namespace std;

class AlternatingVoteStrategy: public GameStrategy {
public:

    AlternatingVoteStrategy(string &File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~AlternatingVoteStrategy() override = default;
private:
    Choice PreviousTurn = DEFECT;
};


#endif //LAB2_ALTERNATINGVOTESTRATEGY_H
