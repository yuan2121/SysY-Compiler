//
// Created by 86152 on 17/11/2023.
//
#include "Def.h"
#include "Exp.h"
#include "LVal.h"
#include <vector>
#include <typeinfo>

using namespace std;

#ifndef MID_CODE_CONSTDEF_H
#define MID_CODE_CONSTDEF_H


class ConstDef : public Def {
public:
    vector<Exp *> *init;
    vector<int> *value = new vector<int>();

    ConstDef(LVal *lVal, vector<Exp *> *init) :
            Def(lVal) {
        this->init = init;
    }

    void out() override {

        if (intTable->getOutTable() == nullptr) {//全局变量
            for (int i = 0; i < init->size(); i++) {
                value->push_back((*init)[i]->cal());    //计算每一个初始值，并存入另一个数组中
            }
            string name = lVal->op.getName();
            if (typeid(*lVal) == typeid(Var)) {
                outDefPrint(name, true, (*value)[0]);
                intTable->addInt(name, *new IntIdent(name, (*value)[0], true));
            } else if (typeid(*lVal) == typeid(Array)) {
                Array *arr = dynamic_cast<Array *>(lVal);
                Exp *exp1 = arr->getExp1();
                Exp *exp2 = arr->getExp2();
                int num1 = exp1->cal();
                if (exp2 == nullptr) {
                    intTable->addInt(name, *new IntIdent(true, name, 1, num1, value));
                    if (!value->empty())
                        outarr(name, true, num1, *value);
                    else
                        outarr(name, true, num1);
                } else {
                    int num2 = exp2->cal();
                    intTable->addInt(name, *new IntIdent(true, name, 2, num1, num2, value));
                    if (!value->empty())
                        outarr(name, true, num1 * num2, *value);
                    else
                        outarr(name, true, num1 * num2);
                }
            }
        } else {
            string name = lVal->op.getName();
            if (typeid(*lVal) == typeid(Var)) {
                if (init->size() == 0) {
                    Reg *reg = new Reg();
                    myalloca(reg->toString());
                    int id = reg->getID();
                    delete reg;
                    intTable->addInt(name, *new IntIdent(name, false, id));
                } else {
                    Reg *reg1 = new Reg();
                    myalloca(reg1->toString());
                    Exp *exp = (*init)[0];
                    string reg2 = exp->genIR();
                    mystore(reg2, reg1->toString());
                    int id = reg1->getID();
                    delete reg1;
                    intTable->addInt(name, *new IntIdent(name, false, id));
                }
            } else if (typeid(*lVal) == typeid(Array)) {
                Array *arr = dynamic_cast<Array *>(lVal);
                Exp *exp1 = arr->getExp1();
                Exp *exp2 = arr->getExp2();
                int num1 = exp1->cal();
                int num2 = 0;
                Reg *reg = new Reg();
                if (exp2 == nullptr) {
                    intTable->addInt(name, *new IntIdent(false, name, 1, num1, reg->getID()));
                    myalloca(reg->toString(), num1);
                } else {
                    num2 = exp2->cal();
                    intTable->addInt(name, *new IntIdent(false, name, 2, num1, num2, reg->getID()));
                    myalloca(reg->toString(), num1 * num2);
                }
                if (!init->empty()) {
                    int k = 0;
                    for (int i = 0; i < init->size(); i++) {

                        int n = (num2 == 0) ? num1 : num1 * num2;
                        Reg *reg1 = new Reg();
                        getelementptr(reg1->toString(), reg->toString(), k++, n);//reg1是指针
                        mystore((*init)[i]->genIR(), reg1->toString());
                        delete (reg1);

                    }
                }
                delete (reg);
            }


//                Array *arr = dynamic_cast<Array *>(lVal);
//                Exp *exp1 = arr->getExp1();
//                Exp *exp2 = arr->getExp2();
//                int num1 = exp1->cal();
//                int num2 = 0;
//                Reg *reg = new Reg();
//                if (exp2 == nullptr) {
//                    intTable->addInt(name, *new IntIdent(false, name, 1, num1, reg->getID()));
//                    myalloca(reg->toString(), num1);
//                } else {
//                    num2 = exp2->cal();
//                    intTable->addInt(name, *new IntIdent(false, name, 2, num1, num2, reg->getID()));
//                    myalloca(reg->toString(), num1 * num2);
//                }
//                if (!value->empty()) {
//                    int k = 0;
//                    for (int i = 0; i < value->size(); i++) {
//                        int n = (num2 == 0) ? num1 : num1 * num2;
//                        Reg *reg1 = new Reg();
//                        getelementptr(reg1->toString(), reg->toString(), k++, n);//reg1是指针
//                        mystore(to_string((*value)[i]), reg1->toString());
//                        delete (reg1);
//                    }
//                }
//                delete (reg);
        }
    }

};


#endif //MID_CODE_CONSTDEF_H
