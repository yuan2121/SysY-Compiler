//
// Created by 86152 on 6/10/2023.
//
#include <string>
#include <vector>

using namespace std;

#ifndef LEXER_IDENT_H
#define LEXER_IDENT_H


class IntIdent {
private:
    int dimension = 0;
    int level1 = 0;
    int level2 = 0;
    int line = 0;
    string name;
    bool Const = false;
    int value = 0;
    int regNum = 0;
    bool isOut = false;
    vector<int> *values = new vector<int>();
    bool ispara = false;

public:
    IntIdent(bool isOut1, string name1, int dimension1, int level1, int level2, vector<int> *values1) {//全局
        dimension = dimension1;
        this->level1 = level1;
        this->level2 = level2;
        name = name1;
        isOut = isOut1;
        values = values1;
    }

    IntIdent(bool isOut1, string name1, int dimension1, int level1, vector<int> *values1) {//全局
        dimension = dimension1;
        this->level1 = level1;
        name = name1;
        isOut = isOut1;
        values = values1;
    }

    IntIdent(bool isOut1, string name1, int dimension1, int level1, int level2, int id) {//局部数组
        dimension = dimension1;
        this->level1 = level1;
        this->level2 = level2;
        name = name1;
        isOut = isOut1;
        regNum = id;
    }

    IntIdent(bool isOut1, string name1, int dimension1, int level1, int level2, int id, bool ispara1) {//局部数组
        dimension = dimension1;
        this->level1 = level1;
        this->level2 = level2;
        name = name1;
        isOut = isOut1;
        regNum = id;
        ispara = ispara1;
    }

    IntIdent(bool isOut1, string name1, int dimension1, int level1, int id) {//局部数组
        dimension = dimension1;
        this->level1 = level1;
        name = name1;
        isOut = isOut1;
        regNum = id;
    }

    IntIdent(bool isOut1, string name1, int dimension1, int level1, int id, bool ispara1) {//局部数组
        dimension = dimension1;
        this->level1 = level1;
        name = name1;
        isOut = isOut1;
        regNum = id;
        ispara = ispara1;
    }

    IntIdent(string name1, int line1, int dimension1, bool Const1) {
        dimension = dimension1;
        line = line1;
        name = name1;
        Const = Const1;
    }

    IntIdent() {

    }

    IntIdent(string name1, int value1, bool isOut1) {//全局
        name = name1;
        value = value1;
        isOut = isOut1;
    }

    IntIdent(string name1, bool isOut1, int reg1) {//局部
        name = name1;
        regNum = reg1;
        isOut = isOut1;
    }

    string getName() {
        return name;
    }

    int getLine() {
        return line;
    }

    bool getIsOut() {
        return isOut;
    }

    int getRegNum() {
        return regNum;
    }

    int getDimension() {
        return dimension;
    }

    bool isConst() {
        return Const;
    }

    void setLine(int line1) {
        line = line1;
    }

    void setDimension(int a) {
        dimension = a;
    }

    int getValue() {
        return value;
    }

    int calAll() {
        if (dimension == 1) {
            return level1;
        } else if (dimension == 2) {
            return level1 * level2;
        }
    }

    int calAddr(int k1, int k2) {
        return k1 * level2 + k2;
    }

    int getLevel2() {
        return level2;
    }

    bool isPara() {
        return ispara;
    }

};


#endif //LEXER_IDENT_H
