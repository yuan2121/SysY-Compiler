//
// Created by 86152 on 15/11/2023.
//
#include "BlockItem.h"
#include "Def.h"
using namespace std;

#ifndef ERROR_DECL_H
#define ERROR_DECL_H

class Decl : public BlockItem{
private:
    vector<Def*>* defs;
    bool isConst;

public:
    Decl(vector<Def*>* defs, bool isConst) {
        this->defs = defs;
        this->isConst = isConst;
    }

    void out() override {
        for (Def* d : *defs) {
            d->out();
        }
    }

};

#endif //ERROR_DECL_H
