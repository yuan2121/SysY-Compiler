//
// Created by 86152 on 18/11/2023.
//
#include "Stmt.h"
#include "../Label.h"

//using namespace std;

#ifndef MID_CODE_IF_H
#define MID_CODE_IF_H


class If : public Stmt{
public:
    OrExp* orExp;
    Stmt* stmt1;
    Stmt* stmt2;
    int label1;
    int label2;

    If(OrExp* orExp, Stmt* stmt1, Stmt* stmt2) {
        this->orExp = orExp;
        this->stmt1 = stmt1;
        this->stmt2 = stmt2;
    }

    void out() override {
        if (stmt2 == nullptr) {
            label1 = ++labels;
            orExp->out(label1);
            if (stmt1 != nullptr) {
                stmt1->out();
            }
            mybr("%l" + to_string(label1));
            mylabel("l" + to_string(label1));
        } else {
            label1 = ++labels;
            label2 = ++labels;
            orExp->out(label1);
            if (stmt1 != nullptr) {
                stmt1->out();
            }
            mybr("%l" + to_string(label2));
            mylabel("l" + to_string(label1));
            stmt2->out();
            mybr("%l" + to_string(label2));
            mylabel("l" + to_string(label2));
        }
    }
};


#endif //MID_CODE_IF_H
