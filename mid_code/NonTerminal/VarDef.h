//
// Created by 86152 on 17/11/2023.
//
#include "Def.h"
#include "../Reg.h"

using namespace std;

#ifndef MID_CODE_VARDEF_H
#define MID_CODE_VARDEF_H


class VarDef : public Def {
public:
    vector<vector<Exp *> *> *init = nullptr;
    vector<int> *value = new vector<int>();

    VarDef(LVal *lVal1, vector<vector<Exp *> *> *init1)
            : Def(lVal1), init(init1) {
    }

    void out() override {
        if (intTable->getOutTable() == nullptr) {//全局变量
            string name = lVal->op.getName();
            if (typeid(*lVal) == typeid(Var)) {
                if (init->empty()) {
                    int value1 = 0;
                    outDefPrint(name, false, value1);
                    intTable->addInt(name, *new IntIdent(name, value1, true));
                } else {
                    Exp *exp = (*(*init)[0])[0];
                    int value1 = exp->cal();
                    outDefPrint(name, false, value1);
                    intTable->addInt(name, *new IntIdent(name, value1, true));
                }
            } else if (typeid(*lVal) == typeid(Array)) {
                for (int i = 0; i < init->size(); i++) {
                    for (int j = 0; j < (*init)[i]->size(); j++) {
                        value->push_back((*(*init)[i])[j]->cal());    //计算初始值，并存入另一个数组中
                    }
                }
                Array *arr = dynamic_cast<Array *>(lVal);
                Exp *exp1 = arr->getExp1();
                Exp *exp2 = arr->getExp2();
                int num1 = exp1->cal();
                if (exp2 == nullptr) {
                    intTable->addInt(name, *new IntIdent(true, name, 1, num1, value));
                    if (!value->empty())
                        outarr(name, false, num1, *value);
                    else
                        outarr(name, false, num1);
                } else {
                    int num2 = exp2->cal();
                    intTable->addInt(name, *new IntIdent(true, name, 2, num1, num2, value));
                    if (!value->empty())
                        outarr(name, false, num1 * num2, *value);
                    else
                        outarr(name, false, num1 * num2);
                }
            }
        } else {//局部变量
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
                    Exp *exp = (*(*init)[0])[0];
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
                    myalloca(reg->toString(), num1*num2);
                }
                if (!init->empty()) {
                    int k = 0;
                    for (int i = 0; i < init->size(); i++) {
                        for (int j = 0; j < (*init)[i]->size(); j++) {
                            int n = (num2==0) ? num1:num1*num2;
                            Reg *reg1 = new Reg();
                            getelementptr(reg1->toString(), reg->toString(), k++, n);//reg1是指针
                            mystore((*(*init)[i])[j]->genIR(), reg1->toString());
                            delete(reg1);
                        }
                    }
                }
                delete(reg);
            }
        }
    }
};


#endif //MID_CODE_VARDEF_H
