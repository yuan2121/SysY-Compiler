//
// Created by 86152 on 18/11/2023.
//
#include "Stmt.h"

using namespace std;

#ifndef MID_CODE_GETINT_H
#define MID_CODE_GETINT_H


class Getint : public Stmt{
public:
    LVal* lVal;
    explicit Getint(LVal* lVal1) : lVal(lVal1) {

    }

    void out() override {
        Reg *reg_in = new Reg();
        mygetint(reg_in->toString());
//        IntIdent ident = intTable->outGet(lVal->op.getName());
//        if (ident.getIsOut()) {
//            string name = "@" + ident.getName();
//            mystore(reg->toString(), name);
//        } else {
//            string id = "%a" + to_string(ident.getRegNum());
//            mystore(reg->toString(), id);
//        }

        if (typeid(*lVal) == typeid(Var)) {
            if (intTable->outGet(lVal->op.getName()).getIsOut()) {
                mystore(reg_in->toString(), "@" + lVal->op.getName());
            } else {
                mystore(reg_in->toString(), "%a" + to_string(intTable->outGet(lVal->op.getName()).getRegNum()));
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
                mystore(reg_in->toString(), reg1->toString());
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
                    mystore(reg_in->toString(), reg1->toString());
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
                    mystore(reg_in->toString(), reg1->toString());
                }
                delete reg1;
            }
        }
    }

};


#endif //MID_CODE_GETINT_H
