//
// Created by 86152 on 6/10/2023.
//
#include <iostream>
#include "Lexer.h"
#include "NonTerminal.h"
#include <fstream>
#include <vector>

using namespace std;

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H


class Parser {
private:
    Lexer lexer;
    Root* root = new Root();

public:
    explicit Parser(Lexer& lexer1);
    static void error() {
        printf("error\n");
    }
    void analyse();
    void CompUnit();
    Decl* Decl();
    class Decl* ConstDecl();
    Def* ConstDef();
    void ConstInitVal(vector<class Exp*>* exp);
    class Decl* VarDecl();
    Def* VarDef();
    void InitVal(vector<vector<class Exp*>*>* exps, int level);
    Func* FuncDef();
    Func* MainFuncDef();
    class Exp* ConstExp();
    Exp* Exp();
    string FuncType();
    vector<FParam*>* FuncFParams();
    vector<class Exp*>* FuncRParams();
    Block* Block();
    FParam* FuncFParam();
    BlockItem* BlockItem();
    Stmt* Stmt();
    class LVal* LVal();
    OrExp* Cond();
    ForStmt* ForStmt();
    void FormatString();
    class Exp* AddExp();
    OrExp* LOrExp();
    class Exp* PrimaryExp();
    class Exp* Number();
    class Exp* UnaryExp();
    Token UnaryOp();
    class Exp* MulExp();
    class Exp* RelExp();
    class Exp* EqExp();
    AndExp* LAndExp();
    void Ident2();
    void Exp2();
    void AddExp2();
    void MulExp2();
    void UnaryExp2();
    void PrimaryExp2();
    void LVal2();
    void FuncRParams2();
//    void FuncRParam2();
    void Cond2();
    void RelExp2();
    void LOrExp2();
    void EqExp2();
    void LAndExp2();
    void ConstExp2();
};


#endif //LEXER_PARSER_H
