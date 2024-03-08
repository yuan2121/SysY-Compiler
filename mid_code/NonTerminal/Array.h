//
// Created by 86152 on 17/11/2023.
//
#include "LVal.h"
#include "Exp.h"
#include "../Token.h"

using namespace std;

#ifndef MID_CODE_ARRAY_H
#define MID_CODE_ARRAY_H


class Array : public LVal {
private:
    int dimension = 0;
    Exp *exp1 = nullptr;
    Exp *exp2 = nullptr;
    bool Const;
public:
    Array(Token token1, Exp *exp1, Exp *exp2, bool const1) : LVal(token1) {
        this->exp1 = exp1;
        this->exp2 = exp2;
        dimension = 2;
        Const = const1;
    }

    Array(Token token1, Exp *exp1, bool const1) : LVal(token1) {
        this->exp1 = exp1;
        dimension = 1;
        Const = const1;
    }

    string genIR() override {
        IntIdent id = intTable->outGet(op.getName());
        if (id.getIsOut()) {
            Reg *reg = new Reg();
            Reg *reg1 = new Reg();
            if (dimension == 1) {
                if (id.getDimension() == 1)
                    getelementptr(reg1->toString(), "@" + op.getName(), exp1->genIR(), id.calAll());
                else if (id.getDimension() == 2) {
                    Reg *reg2 = new Reg();
                    irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
//                    Reg *reg3 = new Reg();
//                    irPrint(reg3->toString(), "+", exp2->genIR(), reg2->toString());
                    getelementptr(reg1->toString(), "@" + op.getName(), reg2->toString(), id.calAll());
                    string reg1Id = reg1->toString();
                    delete reg2, reg1, reg;
                    return reg1Id;
                }
            } else if (dimension == 2) {
                Reg *reg2 = new Reg();
                irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
                Reg *reg3 = new Reg();
                irPrint(reg3->toString(), "+", exp2->genIR(), reg2->toString());
                getelementptr(reg1->toString(), "@" + op.getName(), reg3->toString(), id.calAll());
                delete reg2, reg3;
            }
            myload(reg->toString(), reg1->toString());
            string regId = reg->toString();
            delete reg, reg1;
            return regId;
        } else {
            if (id.isPara()) {
                int num = id.getRegNum();
                Reg *reg = new Reg();
                Reg *reg1 = new Reg();
                if (dimension == 1) {
                    if (id.getDimension() == 1) {
                        Reg *reg2 = new Reg();
                        myload1(reg2->toString(), "%a" + to_string(num));
                        getelementptr(reg1->toString(), reg2->toString(), exp1->genIR());
                        delete reg2;
                    } else if (id.getDimension() == 2) {
                        Reg *reg2 = new Reg();
                        Reg *reg3 = new Reg();
                        myload1(reg3->toString(), "%a" + to_string(num));
                        irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
                        getelementptr(reg1->toString(), reg3->toString(), reg2->toString());
                        string reg1Id = reg1->toString();
                        delete reg2, reg1, reg, reg3;
                        return reg1Id;
                    }
                } else if (dimension == 2) {
                    Reg *reg2 = new Reg();
                    Reg *reg4 = new Reg();
                    myload1(reg4->toString(), "%a" + to_string(num));
                    irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
                    Reg *reg3 = new Reg();
                    irPrint(reg3->toString(), "+", exp2->genIR(), reg2->toString());
                    getelementptr(reg1->toString(), reg4->toString(), reg3->toString());
                    delete reg2, reg3, reg4;
                }
                myload(reg->toString(), reg1->toString());
                string id = reg->toString();
                delete reg, reg1;
                return id;
            } else {
                int num = id.getRegNum();
                Reg *reg = new Reg();
                Reg *reg1 = new Reg();
                if (dimension == 1) {
                    if (id.getDimension() == 1)
                        getelementptr(reg1->toString(), "%a" + to_string(num), exp1->genIR(), id.calAll());
                    else if (id.getDimension() == 2) {
                        Reg *reg2 = new Reg();
                        irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
//                    Reg *reg3 = new Reg();
//                    irPrint(reg3->toString(), "+", exp2->genIR(), reg2->toString());
                        getelementptr(reg1->toString(), "%a" + to_string(num), reg2->toString(), id.calAll());
                        string reg1Id = reg1->toString();
                        delete reg2, reg1, reg;
                        return reg1Id;
                    }
                } else if (dimension == 2) {
                    Reg *reg2 = new Reg();
                    irPrint(reg2->toString(), "*", exp1->genIR(), to_string(id.getLevel2()));
                    Reg *reg3 = new Reg();
                    irPrint(reg3->toString(), "+", exp2->genIR(), reg2->toString());
                    getelementptr(reg1->toString(), "%a" + to_string(num), reg3->toString(), id.calAll());
                    delete reg2, reg3;
                }
                myload(reg->toString(), reg1->toString());
                string id = reg->toString();
                delete reg, reg1;
                return id;
            }
        }
    }

    int getDimension() {
        return dimension;
    }

    bool isConst() {
        return Const;
    }

    Exp *getExp1() {
        return exp1;
    }

    Exp *getExp2() {
        return exp2;
    }
};


#endif //MID_CODE_ARRAY_H
