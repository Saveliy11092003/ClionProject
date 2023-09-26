//
// Created by user on 11.11.22.
//

#include "Button.h"

Action Button::CheckStatusButton(string StatusButtonNow) {
    if(this->StatusButton == StatusButtonNow){
        return Stop;
    }
    else{
        return Continue;
    }
}

Button::Button() {
    StatusButton = "quit";
}
