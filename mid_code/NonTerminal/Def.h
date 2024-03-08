//
// Created by 86152 on 15/11/2023.
//

#ifndef ERROR_DEF_H
#define ERROR_DEF_H

#include "Node.h"
#include "LVal.h"

class Def : public Node{
public:
    LVal* lVal;

    Def(LVal* lVal) {
        this->lVal = lVal;
    }

};

#endif //ERROR_DEF_H
