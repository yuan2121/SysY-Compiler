//
// Created by 86152 on 11/11/2023.
//

#ifndef ERROR_STRTOKEN_H
#define ERROR_STRTOKEN_H

#include "Token.h"

class StrToken : public Token {
private :
    int expNum;

public:
    StrToken(string name1, LexType type1, int line1, int expNum1)
    : Token(name1, type1, line1), expNum(expNum1) {

    }

    int getNum() {
        return expNum;
    }

};

#endif //ERROR_STRTOKEN_H
