//
// Created by 86152 on 18/11/2023.
//

#ifndef MID_CODE_CONTINUE_H
#define MID_CODE_CONTINUE_H


#include "Stmt.h"

using namespace std;

class Continue : public Stmt{
public:
    Continue() = default;

    void out() override {
        int n = myStack.top();
        mybr("%fori" + to_string(n));
    }
};


#endif //MID_CODE_CONTINUE_H
