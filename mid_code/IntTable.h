//
// Created by 86152 on 11/10/2023.
//
#include <iostream>
#include <map>
#include "NonTerminal/IntIdent.h"

using namespace std;

#ifndef LEXER_INTTABLE_H
#define LEXER_INTTABLE_H

class IntTable{
private:
map<string,IntIdent> inTable;
IntTable *outTable = nullptr;

public:
    IntTable() {

    }

    map<string,IntIdent> getInTable() {
        return inTable;
    }

    void setOutTable(IntTable *outTable1){
        outTable = outTable1;
    }

    IntTable* getOutTable() {
        return outTable;
    }

    void addInt(string str, IntIdent ident) {
        inTable.insert({str,ident});
    }

    int contain(string str) {
        return inTable.count(str);
    }

    bool outContain(string str) {
        if (contain(str)) {
            return true;
        }
        IntTable *table = outTable;
        while (table != nullptr) {                      //未定义名字c类错误
            if (table->contain(str)) {
                return true;
            }
            table = table->getOutTable();
        }
        return false;
    }

    IntIdent outGet(string str) {
        if (contain(str)) {
            return inTable[str];
        }
        IntTable *table = outTable;
        while (table != nullptr) {                      //未定义名字c类错误
            if (table->contain(str)) {
                return table->getInTable()[str];
            }
            table = table->getOutTable();
        }
        return *(new IntIdent());
    }

};

#endif //LEXER_INTTABLE_H
