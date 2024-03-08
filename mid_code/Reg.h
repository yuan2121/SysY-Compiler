//
// Created by 86152 on 21/11/2023.
//
#include <string>

using namespace std;
#ifndef MID_CODE_REG_H
#define MID_CODE_REG_H


class Reg {
private:
    static int count;
    int id;

public:
    Reg() {
        id = ++count;
    }

    int getID() {
        return id;
    }

    string toString() {
        return "%a" + to_string(id);
    }
};


#endif //MID_CODE_REG_H
