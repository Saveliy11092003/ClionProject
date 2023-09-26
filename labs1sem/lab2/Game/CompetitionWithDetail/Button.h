//
// Created by user on 11.11.22.
//

#ifndef LAB2_BUTTON_H
#define LAB2_BUTTON_H

#include <string>

using namespace std;

enum Action{
    Stop,
    Continue
};

class Button {
private:
    string StatusButton;
public:
    Button();
    Action CheckStatusButton(string StatusButtonNow);
};


#endif //LAB2_BUTTON_H
