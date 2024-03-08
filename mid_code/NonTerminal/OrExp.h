//
// Created by 86152 on 17/11/2023.
//
#include "AndExp.h"

#ifndef MID_CODE_OREXP_H
#define MID_CODE_OREXP_H

class OrExp : public Node {
public:
    vector<AndExp*> *ands = new vector<AndExp*>();
    int label;

    explicit OrExp(vector<AndExp*> *ands1) : ands(ands1) {
//        num = ++count;
        label = 0;
    }

    void out(int n) {
        this->label = ++labels;
        for(AndExp* a: *ands){
            a->out(label);
        }
        mybr("%l" + to_string(n));
        mylabel("l" + to_string(label));
    }

    void out(int n, int flag) {
        this->label = ++labels;
        for(AndExp* a: *ands){
            a->out(label);
        }
        mybr("%forend" + to_string(n));
        mylabel("l" + to_string(label));
    }
};

#endif //MID_CODE_OREXP_H
