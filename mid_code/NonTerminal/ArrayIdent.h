//
// Created by 86152 on 12/12/2023.
//
#include <string>
#include "IntIdent.h"
#include <vector>
using namespace std;

#ifndef MID_CODE_ARRAYIDENT_H
#define MID_CODE_ARRAYIDENT_H

class ArrayIdent : public IntIdent{
private:
    string name;
    int dimension = 0;
    int level1 = 0;
    int level2 = 0;
    bool Const = false;
    vector<int>* value = new vector<int>();
    bool isOut = true;

public:
    ArrayIdent(bool isOut1, string name1, int dimension1, int level1, int level2) {
        dimension = dimension1;
        this->level1 = level1;
        this->level2 = level2;
        name = name1;
        isOut = isOut1;
    }

    ArrayIdent(bool isOut1, string name1, int dimension1, int level1) {
        dimension = dimension1;
        this->level1 = level1;
        name = name1;
        isOut = isOut1;
    }


};

#endif //MID_CODE_ARRAYIDENT_H
