//
// Created by 86152 on 18/11/2023.
//
#include "Node.h"

using namespace std;

#ifndef MID_CODE_FORSTMT_H
#define MID_CODE_FORSTMT_H


class ForStmt : public Node{
    // ForStmt → LVal '=' Exp
public:
    LVal* lVal;
    Exp* exp;

    ForStmt(LVal* lVal1, Exp* exp1) : lVal(lVal1), exp(exp1) {

    }

    void out() override {
        if (typeid(*lVal) == typeid(Var)) {
            if (intTable->outGet(lVal->op.getName()).getIsOut()) {
                mystore(exp->genIR(), "@"+lVal->op.getName());
            } else{
                mystore(exp->genIR(), "%a"+ to_string(intTable->outGet(lVal->op.getName()).getRegNum()));
            }
        } else {

        }
    }
};


#endif //MID_CODE_FORSTMT_H
