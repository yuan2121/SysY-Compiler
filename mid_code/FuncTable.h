//
// Created by 86152 on 13/10/2023.
//
#include <map>
#include <string>
#include "NonTerminal/FuncIdent.h"

using namespace std;

#ifndef ERROR_FUNCTABLE_H
#define ERROR_FUNCTABLE_H

class FuncTable {
private:
    map<string, FuncIdent> inTable;
    FuncTable *outTable;

public:
    map<string, FuncIdent> getInTable() {
        return inTable;
    }

    void setOutTable(FuncTable *outTable1) {
        outTable = outTable1;
    }

    FuncTable *getOutTable() {
        return outTable;
    }

    void addFunc(string str, FuncIdent ident) {
        inTable.insert({str, ident});
    }

    int contain(string str) {
        return inTable.count(str);
    }

    bool outContain(string str) {
        if (contain(str)) {
            return true;
        }
        FuncTable *table = outTable;
        while (table != nullptr) {                      //未定义名字c类错误
            if (table->contain(str)) {
                return true;
            }
            table = table->getOutTable();
        }
        return false;
    }

    FuncIdent get(string str) {
        return inTable[str];
    }

};

#endif //ERROR_FUNCTABLE_H
