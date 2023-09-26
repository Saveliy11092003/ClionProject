//
// Created by user on 28.10.22.
//

#include "TitForTatSoft.h"

TitForTatSoft::TitForTatSoft(std::string File, GameMatrix gameMatrix) {

}

Choice TitForTatSoft::vote() {
    if(PreviousTurnFirstOpponent == COOPERATE && PreviousTurnSecondOpponent == COOPERATE ){
        return COOPERATE;
    }
    if(PreviousTurnFirstOpponent == COOPERATE && PreviousTurnSecondOpponent == DEFECT ){
        return COOPERATE;
    }
    if(PreviousTurnFirstOpponent == DEFECT && PreviousTurnSecondOpponent == COOPERATE ){
        return COOPERATE;
    }
    if(PreviousTurnFirstOpponent == DEFECT && PreviousTurnSecondOpponent == DEFECT ){
        return DEFECT;
    }
}

void TitForTatSoft::update(Choice A, Choice B) {
    PreviousTurnFirstOpponent = A;
    PreviousTurnSecondOpponent = B;
}
