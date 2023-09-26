//
// Created by user on 28.10.22.
//

#include "StrategyFactory.h"
#include "../Strategies/Alternating/AlternatingVoteStrategy.h"
#include <stdexcept>



shared_ptr<GameStrategy> StrategyFactory::createStrategy(StrategyName strategyName,
                                              const GameMatrix &gameMatrix) {
    string strAlwaysChoiceC = "strAlwaysChoiceC.txt";

    string strAlwaysChoiceD = "strAlwaysChoiceD.txt";

    string strAlternating = "strAlternating.txt";

    string strTitForTatSoft = "strTitForTatSoft.txt";

    string strTitForTatHard = "TitForTatHard.txt";

    string strRandom = "strRandom.txt";

       switch (strategyName) {
           case ALWAYS_CHOICE_C:
               return shared_ptr<AlwaysVoteCGameStrategy> (new AlwaysVoteCGameStrategy (strAlwaysChoiceC, gameMatrix));

           case ALWAYS_CHOICE_D:
               return shared_ptr<AlwaysVoteDGamesStrategy> (new AlwaysVoteDGamesStrategy (strAlwaysChoiceD, gameMatrix));

           case ALTERNATING:
               return shared_ptr<AlternatingVoteStrategy> (new AlternatingVoteStrategy (strAlternating, gameMatrix));

           case TIT_FOT_TAT_SOFT:
               return shared_ptr<TitForTatSoft> (new TitForTatSoft (strTitForTatSoft, gameMatrix));

           case RANDOM:
               return shared_ptr<RandomStrategy> (new RandomStrategy (strRandom, gameMatrix));

           case TIT_FOT_TAT_HARD:
               return shared_ptr<TitForTatHard> (new TitForTatHard (strTitForTatHard, gameMatrix));
       }
       throw std::exception();
}

StrategyFactory::~StrategyFactory() {
    for (const auto &strategy: strategies) {
        delete strategy;
    }
    strategies.clear();
}

StrategyName  StrategyFactory::DetectionStrategyName(string StringStrategy) {
    auto it = MyMap.find(StringStrategy);
    return it->second;
}

StrategyFactory::StrategyFactory() {
    MyMap.emplace("AlwaysChoiceC", ALWAYS_CHOICE_C);
    MyMap.emplace("AlwaysChoiceD", ALWAYS_CHOICE_D);
    MyMap.emplace("Alternating", ALTERNATING);
    MyMap.emplace("Tit_For_Tat_Soft", TIT_FOT_TAT_SOFT);
    MyMap.emplace("Tit_For_Tat_Hard", TIT_FOT_TAT_HARD);
    MyMap.emplace("Random", RANDOM);
}

