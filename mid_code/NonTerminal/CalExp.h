//
// Created by 86152 on 18/11/2023.
//
#include "Exp.h"
#include "../Reg.h"

using namespace std;

#ifndef MID_CODE_CALEXP_H
#define MID_CODE_CALEXP_H


class CalExp : public Exp {
public :
    Exp *exp1, *exp2;

    CalExp(Token token1, Exp *exp1, Exp *exp2) : Exp(token1) {
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    string genIR() override {
        Reg *reg = new Reg();
        irPrint(reg->toString(), op.getName(), exp1->genIR(), exp2->genIR());
        return reg->toString();
    }

    int cal() override {
        int value = 0;
        int value1 = exp1->cal();
        int value2 = exp2->cal();
        if (op.getName() == "+") {
            value = value1 + value2;
        } else if (op.getName() == "-") {
            value = value1 - value2;
        } else if (op.getName() == "*") {
            value = value1 * value2;
        } else if (op.getName() == "/") {
            value = value1 / value2;
        } else if (op.getName() == "%") {
            value = value1 % value2;
        }
        return value;
    }
};


#endif //MID_CODE_CALEXP_H
