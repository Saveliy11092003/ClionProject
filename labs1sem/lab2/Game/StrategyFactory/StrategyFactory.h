//
// Created by user on 28.10.22.
//

#ifndef LAB2_STRATEGYFACTORY_H
#define LAB2_STRATEGYFACTORY_H


#include <vector>
#include "../GameStrategy.h"
#include "../Strategies/AlwaysVoteC/AlwaysVoteCGameStrategy.h"
#include "../Strategies/AlwaysVoteD/AlwaysVoteDGamesStrategy.h"
#include"../Strategies/Alternating/AlternatingVoteStrategy.h"
#include"../Strategies/RandomStrategy/RandomStrategy.h"
#include"../Strategies/TitForTatHard/TitForTatHard.h"
#include"../Strategies/TitForTatSoft/TitForTatSoft.h"
#include "../GameMatrix/GameMatrix.h"
#include <string>
#include <memory>
#include "map"
#include <fstream>

using namespace std;

class StrategyFactory {

public:
    StrategyFactory();
    StrategyName DetectionStrategyName(string StringStrategy);

    shared_ptr<GameStrategy> createStrategy(StrategyName strategyName,
                                        const GameMatrix &gameMatrix);


    ~StrategyFactory();

private:
    std::vector<GameStrategy *> strategies;
    map<string, StrategyName> MyMap;
};


#endif //LAB2_STRATEGYFACTORY_H
