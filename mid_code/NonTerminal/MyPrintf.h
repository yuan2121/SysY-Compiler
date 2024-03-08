//
// Created by 86152 on 18/11/2023.
//

#ifndef MID_CODE_MYPRINTF_H
#define MID_CODE_MYPRINTF_H

#include <utility>

#include "Stmt.h"

using namespace std;


class MyPrintf : public Stmt {
public:
    Token token;
    vector<Exp*>* exps;

    MyPrintf(Token token1, vector<Exp*>* exps1) : token(move(token1)), exps(exps1) {

    }

    void out() override {
        int n = 0;
        string str = token.getName();
        for (int i = 1; i < str.size()-1; ++i) {
            if (str[i] != '%' && str[i] != '\\') {
                myputch(str[i]);
            } else if (str[i] == '%') {
                string id = (*exps)[n++]->genIR();
                myputint(id);
                ++i;
            } else {
                myputch('\n');
                ++i;
            }
        }
    }
};


#endif //MID_CODE_MYPRINTF_H
