//
// Created by 86152 on 17/11/2023.
//
#include <utility>
#include "Exp.h"
#include "../Token.h"

using namespace std;
#ifndef MID_CODE_LVAL_H
#define MID_CODE_LVAL_H


class LVal : public Exp{
public:
    explicit LVal(Token token1) : Exp(move(token1)) {

    }

    LVal() = default;
};


#endif //MID_CODE_LVAL_H
