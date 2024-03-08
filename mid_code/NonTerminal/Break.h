//
// Created by 86152 on 18/11/2023.
//
#include "Stmt.h"

using namespace std;
#ifndef MID_CODE_BREAK_H
#define MID_CODE_BREAK_H


class Break : public Stmt{
public:
    Break() = default;

    void out() override {
        int n = myStack.top();
        mybr("%forend" + to_string(n));
    }
};


#endif //MID_CODE_BREAK_H
