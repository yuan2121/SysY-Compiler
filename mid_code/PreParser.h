//
// Created by 86152 on 6/10/2023.
//
#include "Lexer.h"
#include "IntTable.h"
#include "FuncTable.h"

#ifndef LEXER_PREPARSER_H
#define LEXER_PREPARSER_H


class PreParser {
private:
    Lexer lexer;
    IntTable* intTable = new IntTable();
    FuncTable* funcTable = new FuncTable();
    string funcType;
    bool inCon = false;
    bool infunc = false;
    bool haveReturn = false;
    int circleNum = 0;
    int arrayLevel = 0;
    int isParam = 0;

public:
    explicit PreParser(Lexer& lexer1);
    void setCir(int n) {
        circleNum = n;
    }
    void addCir() {
        circleNum++;
    }
    void subCir() {
        circleNum--;
    }
    bool isExp(Token token) {
        string name = token.getName();
        LexType type = token.getType();
        if (name == "(" ||name == "+" ||name == "-" ||name == "!") {
            return true;
        } else return type == INTCON || type == IDENFR;
    }
    void error(){
        printf("error\n");
    }
    void CompUnit();
    void Decl();
    void FuncDef();
    void MainFuncDef();
    void ConstDecl();
    void VarDecl();
    void ConstDef();
    void BType();
    void ConstExp();
    void ConstInitVal();
    void VarDef();
    void InitVal();
    void Exp();
    string FuncType();
    vector<IntIdent> FuncFParams();
    vector<int> FuncRParams();

    int Block();
    IntIdent* FuncFParam();
    void BlockItem();
    void Stmt();
    IntIdent LVal();
    void Cond();
    void ForStmt();
    void FormatString();
    void AddExp();
    void LOrExp();
    void PrimaryExp();
    void Number();
//    void IntConst();
    void UnaryExp();
    void UnaryOp();
    void MulExp();
    void RelExp();
    void EqExp();
    void LAndExp();
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


#endif //LEXER_PREPARSER_H
