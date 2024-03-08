//
// Created by 86152 on 18/11/2023.
//

#ifndef MID_CODE_MYRETURN_H
#define MID_CODE_MYRETURN_H

#include "Stmt.h"
#include "../Reg.h"

using namespace std;

class MyReturn : public Stmt {
public:
    Exp *exp;

    explicit MyReturn(Exp *exp1) : exp(exp1) {

    }

    void out() override {
        if (exp == nullptr) {
            fout << "ret void" << endl;
        } else {
            retPrint(exp->genIR());
        }
    }
};


#endif //MID_CODE_MYRETURN_H
