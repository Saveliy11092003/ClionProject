//
// Created by user on 17.11.22.
//

#include "AlternatingVoteStrategy.h"

AlternatingVoteStrategy::AlternatingVoteStrategy(string &File, GameMatrix gameMatrix) {
}

Choice AlternatingVoteStrategy::vote() {
    if(PreviousTurn == DEFECT){
        PreviousTurn = COOPERATE;
        return COOPERATE;
    }
    else{
        PreviousTurn = DEFECT;
        return DEFECT;
    }
}

void AlternatingVoteStrategy::update(Choice A, Choice B) {

}
