#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

class Lexer {
private:
    int lineNum;
    string src;
    int curPos;
    map<string, LexType> keywords;
    vector<Token> srcList;
    int store;
    int index;

public:

    Lexer(string src, map<string, LexType> keywords);

    bool isKeywords(string str);

    void dealNum(string str);

    void dealAlpha(string str);

    void dealString(string str);

    void lexerDeal(string str);

    vector<Token> getSrcList();

    void next();

    Token peek();

    bool isEnd();

    int getIndex();

    void setRemove(int a);

    void remove();

    int getLine();

    int getPreLine();

    void resetIndex() {
        index = 0;
    }
};

#endif //LEXER_LEXER_H
