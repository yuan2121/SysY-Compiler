//
// Created by 86152 on 18/11/2023.
//
#include "Exp.h"

using namespace std;

#ifndef MID_CODE_NUMBER_H
#define MID_CODE_NUMBER_H


class Number : public Exp{
public:
    explicit Number(Token token1) : Exp(token1){

    }

    string genIR() override {
        return op.getName();
    }

    int cal() override {
        return stoi(op.getName());
    }
};


#endif //MID_CODE_NUMBER_H
