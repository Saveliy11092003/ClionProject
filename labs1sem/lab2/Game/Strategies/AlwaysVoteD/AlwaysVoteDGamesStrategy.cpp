//
// Created by user on 28.10.22.
//

#include "AlwaysVoteDGamesStrategy.h"


AlwaysVoteDGamesStrategy::AlwaysVoteDGamesStrategy(string File, GameMatrix gameMatrix) {
}

Choice AlwaysVoteDGamesStrategy::vote() {
    return DEFECT;
}

void AlwaysVoteDGamesStrategy::update(Choice A, Choice B) {

}
