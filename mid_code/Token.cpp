//
// Created by 86152 on 22/9/2023.
//

#include "Token.h"
#include <iostream>

using namespace std;

int Token::getLine() {
    return line;
}

string Token::getName() {
    return name;
}

LexType Token::getType() {
    return type;
}