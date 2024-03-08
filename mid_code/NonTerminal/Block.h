//
// Created by 86152 on 15/11/2023.
//
#include "Stmt.h"

#ifndef ERROR_BLOCK_H
#define ERROR_BLOCK_H


class Block : public Stmt {
public:
    vector<BlockItem*> *blockItems;
//    static int count;
//    int num;

    explicit Block(vector<BlockItem*> *blockItems) {
        this->blockItems = blockItems;
//        num = ++count;
    }

    void out() override {
        IntTable *newTable = new IntTable();               //进入函数创建一个新的作用域
        newTable->setOutTable(intTable);
        intTable = newTable;
        //mylabel("b" + to_string(num));
        if (blockItems != nullptr) {
            for (BlockItem* it : *blockItems) {
                it->out();
            }
        }
        intTable = intTable->getOutTable();
    }
};


#endif //ERROR_BLOCK_H
