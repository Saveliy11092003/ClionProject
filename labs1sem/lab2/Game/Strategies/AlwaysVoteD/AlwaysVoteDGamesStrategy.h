//
// Created by user on 28.10.22.
//

#ifndef LAB2_ALWAYSVOTEDGAMESSTRATEGY_H
#define LAB2_ALWAYSVOTEDGAMESSTRATEGY_H

#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>

using namespace std;

class AlwaysVoteDGamesStrategy: public GameStrategy {
public:

    AlwaysVoteDGamesStrategy(string File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~AlwaysVoteDGamesStrategy() override = default;
};


#endif //LAB2_ALWAYSVOTEDGAMESSTRATEGY_H
