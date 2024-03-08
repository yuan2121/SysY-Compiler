#include <utility>
#include "../Reg.h"

using namespace std;
//
// Created by 86152 on 17/11/2023.
//

#ifndef MID_CODE_VAR_H
#define MID_CODE_VAR_H


class Var : public LVal {//int和func
public:
    explicit Var(Token token1) : LVal(move(token1)) {

    }

    int cal() override {
        return intTable->outGet(op.getName()).getValue();
    }

    string genIR() override {
        IntIdent ident = intTable->outGet(op.getName());
        if (ident.getIsOut()) {
            if (ident.getDimension() == 0) {
                Reg *reg = new Reg();
                myload(reg->toString(), "@" + op.getName());
                string id = reg->toString();
                delete reg;
                return id;
            } else {
                Reg *reg1 = new Reg();
                getelementptr(reg1->toString(), "@" + op.getName(), "0", ident.calAll());
                string reg1Id = reg1->toString();
                delete reg1;
                return reg1Id;
            }
        } else {
            if (ident.getDimension() == 0) {
                int num = intTable->outGet(op.getName()).getRegNum();
                Reg *reg = new Reg();
                myload(reg->toString(), "%a" + to_string(num));
                string id = reg->toString();
                delete reg;
                return id;
            } else {
                if (ident.isPara()) {
                    int num = intTable->outGet(op.getName()).getRegNum();
                    Reg *reg1 = new Reg();
                    Reg *reg2 = new Reg();
                    myload1(reg2->toString(), "%a" + to_string(num));
                    getelementptr(reg1->toString(), reg2->toString(), "0");
                    string reg1Id = reg1->toString();
                    delete reg1;
                    return reg1Id;
                } else {
                    int num = intTable->outGet(op.getName()).getRegNum();
                    Reg *reg1 = new Reg();
                    getelementptr(reg1->toString(), "%a" + to_string(num), "0", ident.calAll());
                    string reg1Id = reg1->toString();
                    delete reg1;
                    return reg1Id;
                }
            }
        }
    }
};


#endif //MID_CODE_VAR_H
