//
// Created by user on 17.11.22.
//

#include "TitForTatHard.h"

TitForTatHard::TitForTatHard(string File, GameMatrix gameMatrix) {

}

Choice TitForTatHard::vote() {
    if(PreviousTurnFirstOpponent == COOPERATE && PreviousTurnSecondOpponent == COOPERATE ){
        return COOPERATE;
    }
    if(PreviousTurnFirstOpponent == COOPERATE && PreviousTurnSecondOpponent == DEFECT ){
        return DEFECT;
    }
    if(PreviousTurnFirstOpponent == DEFECT && PreviousTurnSecondOpponent == COOPERATE ){
        return DEFECT;
    }
    if(PreviousTurnFirstOpponent == DEFECT && PreviousTurnSecondOpponent == DEFECT ){
        return DEFECT;
    }
}

void TitForTatHard::update(Choice A, Choice B) {
    PreviousTurnFirstOpponent = A;
    PreviousTurnSecondOpponent = B;
}


