//
// Created by 86152 on 18/11/2023.
//
#include "Exp.h"
#include <utility>
#include "../Reg.h"

using namespace std;

#ifndef MID_CODE_UNARYEXP_H
#define MID_CODE_UNARYEXP_H

class UnaryExp : public Exp {
public:
    Exp *exp;

    UnaryExp(Token token1, Exp *exp1) : Exp(std::move(token1)), exp(exp1) {
    }

    string genIR() override {
        if (op.getName() == "+") {
            return exp->genIR();
        } else if (op.getName() == "-") {
            Reg *reg = new Reg();
            irPrint(reg->toString(), "-", "0", exp->genIR());
            return reg->toString();
        } else if (op.getName() == "!") {
            Reg *reg = new Reg();
            mycmp(reg->toString(), "==", "0", exp->genIR());
            Reg *reg1 = new Reg();
            myZext(reg1->toString(), reg->toString(), 1, 32);
            return reg1->toString();
        } else {
            return "";
        }
    }

    int cal() override {
        if (op.getName() == "-") {
            return exp->cal() * (-1);
        } else {
            return exp->cal();
        }
    }
};


#endif //MID_CODE_UNARYEXP_H
