//
// Created by 86152 on 17/11/2023.
//
#include <utility>
#include "Stmt.h"
#include "../Token.h"

using namespace std;

#ifndef MID_CODE_EXP_H
#define MID_CODE_EXP_H


class Exp : public Stmt{
public:
    Token op;
    explicit Exp(Token op1) : op(move(op1)) {

    }

    Exp() = default;

    virtual int cal() {
        return 0;
    }
};


#endif //MID_CODE_EXP_H
