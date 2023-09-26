//
// Created by user on 28.10.22.
//

#ifndef LAB2_ALWAYSVOTECGAMESTRATEGY_H
#define LAB2_ALWAYSVOTECGAMESTRATEGY_H

#include <string>
#include "../../GameStrategy.h"
#include "../../GameMatrix/GameMatrix.h"
#include <fstream>

using namespace std;
class AlwaysVoteCGameStrategy : public GameStrategy {

public:

    AlwaysVoteCGameStrategy(string &File, GameMatrix gameMatrix);

    Choice vote() override;

    void update(Choice A, Choice B) override;

    ~AlwaysVoteCGameStrategy() override = default;

};



#endif //LAB2_ALWAYSVOTECGAMESTRATEGY_H
