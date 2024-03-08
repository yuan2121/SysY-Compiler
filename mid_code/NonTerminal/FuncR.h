//
// Created by 86152 on 18/11/2023.
//
#include <utility>

#include "Exp.h"

using namespace std;

#ifndef MID_CODE_FUNCR_H
#define MID_CODE_FUNCR_H


class FuncR : public Exp {
public:
    vector<Exp *> *rParams;
    vector<string> *regs = new vector<string>();

    FuncR(Token token1, vector<Exp *> *rParams1) : Exp(std::move(token1)), rParams(rParams1) {

    }

    void out() {
//        fout << genIR() << endl;
        genIR();
    }

    string genIR() override {
        for (Exp *r : *rParams) {
            regs->push_back(r->genIR());
        }
        string str = "";
        string name = op.getName();
        string type = funcTable->get(name).getType();
        if (type == "void") {
            str = str + "call void @" + name + "(";
        } else {
            str = str + "call i32 @" + name + "(";
        }
        if (regs->size() > 0) {
            FuncIdent funcid = funcTable->get(name);
            if (funcid.getPara(0) == 0)
                str = str + "i32 " + (*regs)[0];
            else
                str = str + "i32* " + (*regs)[0];
            for (int i = 1; i < regs->size(); i++) {
                if (funcid.getPara(i) == 0)
                    str = str + ", i32 " + (*regs)[i];
                else
                    str = str + ", i32* " + (*regs)[i];
            }
        }
        str = str + ")";
        if (type == "void") {
            myfuncr(str);
            return "";
        } else {
            Reg *reg = new Reg();
            myfuncr(reg->toString(), str);
            string str1 = reg->toString();
            delete reg;
            return str1;
        }
    }
};


#endif //MID_CODE_FUNCR_H
