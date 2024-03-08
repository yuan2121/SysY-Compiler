//
// Created by 86152 on 17/11/2023.
//
#include "Node.h"
#include "Var.h"
#include "Exp.h"

using namespace std;

#ifndef MID_CODE_FPARAM_H
#define MID_CODE_FPARAM_H

class FParam : public Node {
public:
    Var *var;
    Exp *exp;
    int dimension = 0;

    FParam(Var *var, int dimension, Exp *exp) {
        this->var = var;
        this->dimension = dimension;
        this->exp = exp;
    }

    string genIR() override {
        Reg *reg = new Reg();
        string str = reg->toString();
        delete reg;
        if (dimension == 0)
            return str;
        else
            return "* " + str;
    }

    string getName() {
        return var->op.getName();
    }

};


#endif //MID_CODE_FPARAM_H
