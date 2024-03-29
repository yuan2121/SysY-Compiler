//
// Created by 86152 on 18/11/2023.
//
#include "Stmt.h"
#include <string>

using namespace std;

#ifndef MID_CODE_ASSIGN_H
#define MID_CODE_ASSIGN_H


class Assign : public Stmt {
public:
    LVal *lVal;
    Exp *exp;

    Assign(LVal *lVal1, Exp *exp1) : lVal(lVal1), exp(exp1) {

    }

    void out() override {
        if (typeid(*lVal) == typeid(Var)) {
            if (intTable->outGet(lVal->op.getName()).getIsOut()) {
                mystore(exp->genIR(), "@" + lVal->op.getName());
            } else {
                mystore(exp->genIR(), "%a" + to_string(intTable->outGet(lVal->op.getName()).getRegNum()));
            }
        } else {
            IntIdent id = intTable->outGet(lVal->op.getName());
            int dimension = id.getDimension();
            Array *arr = dynamic_cast<Array *>(lVal);
            Reg *reg1 = new Reg();
            if (id.getIsOut()) {
//                mystore(exp->genIR(), "@"+lVal->op.getName());
                if (dimension == 1) {
                    getelementptr(reg1->toString(), "@" + arr->op.getName(), arr->getExp1()->genIR(), id.calAll());
                } else if (dimension == 2) {
                    Reg *reg2 = new Reg();
                    irPrint(reg2->toString(), "*", arr->getExp1()->genIR(), to_string(id.getLevel2()));
                    Reg *reg3 = new Reg();
                    irPrint(reg3->toString(), "+", arr->getExp2()->genIR(), reg2->toString());
                    getelementptr(reg1->toString(), "@" + arr->op.getName(), reg3->toString(), id.calAll());
                    delete reg2, reg3;
                }
                mystore(exp->genIR(), reg1->toString());
                delete reg1;
            } else {
//                mystore(exp->genIR(), "%a"+ to_string(intTable->outGet(lVal->op.getName()).getRegNum()));
                int num = intTable->outGet(arr->op.getName()).getRegNum();

                Reg *reg1 = new Reg();
                if (id.isPara()) {
                    if (dimension == 1) {
                        Reg *reg2 = new Reg();
                        myload1(reg2->toString(), "%a" + to_string(num));
                        getelementptr(reg1->toString(), reg2->toString(), arr->getExp1()->genIR());
                        delete reg2;
//                        getelementptr(reg1->toString(), "%a" + to_string(num), arr->getExp1()->genIR(), id.calAll());
                    } else if (dimension == 2) {
                        Reg *reg2 = new Reg();
                        Reg *reg3 = new Reg();
                        Reg *reg33 = new Reg();//实际地址
                        myload1(reg33->toString(), "%a" + to_string(num));

                        irPrint(reg2->toString(), "*", arr->getExp1()->genIR(), to_string(id.getLevel2()));
                        irPrint(reg3->toString(), "+", arr->getExp2()->genIR(), reg2->toString());
                        getelementptr(reg1->toString(), reg33->toString(), reg3->toString());
                        delete reg2, reg3, reg33;
                    }
                    mystore(exp->genIR(), reg1->toString());
                } else {
                    if (dimension == 1) {
                        getelementptr(reg1->toString(), "%a" + to_string(num), arr->getExp1()->genIR(), id.calAll());
                    } else if (dimension == 2) {
                        Reg *reg2 = new Reg();
                        irPrint(reg2->toString(), "*", arr->getExp1()->genIR(), to_string(id.getLevel2()));
                        Reg *reg3 = new Reg();
                        irPrint(reg3->toString(), "+", arr->getExp2()->genIR(), reg2->toString());
                        getelementptr(reg1->toString(), "%a" + to_string(num), reg3->toString(), id.calAll());
                        delete reg2, reg3;
                    }
                    mystore(exp->genIR(), reg1->toString());
                }
                delete reg1;
            }
        }
    }
};


#endif //MID_CODE_ASSIGN_H
