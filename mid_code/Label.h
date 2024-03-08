//
// Created by 86152 on 3/12/2023.
//
#include "string"

using namespace std;
#ifndef MID_CODE_LABEL_H
#define MID_CODE_LABEL_H


class Label {
private:
    static int count;
    int id;

public:
    Label() {
        id = ++count;
    }

    int getID() {
        return id;
    }

    string toString() {
        return "l" + to_string(id) + ":\n";
    }
};


#endif //MID_CODE_LABEL_H
