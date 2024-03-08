//
// Created by 86152 on 18/11/2023.
//
#include "Exp.h"

using namespace std;

#ifndef MID_CODE_LOGEXP_H
#define MID_CODE_LOGEXP_H


class LogExp : public Exp {
public:
    Exp *exp1, *exp2;

    LogExp(Token token1, Exp *exp1, Exp *exp2) : Exp(token1) {
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    string genIR() override {
        Reg *reg = new Reg();
        string op = this->op.getName();
        string str1 = exp1->genIR();
        string str2 = exp2->genIR();
        mycmp(reg->toString(), op, str1, str2);
        Reg *reg1 = new Reg();
        myZext(reg1->toString(), reg->toString(), 1, 32);
        return reg1->toString();


//        Reg *reg = new Reg();
//        mycmp(reg->toString(), "==", "0", exp->genIR());
//        Reg *reg1 = new Reg();
//        myZext(reg1->toString(), reg->toString(), 1, 32);
//        return reg1->toString();
    }
};


#endif //MID_CODE_LOGEXP_H
