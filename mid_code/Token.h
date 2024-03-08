#include <iostream>
using namespace std;

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

enum LexType {
    IDENFR, NOT, MULT, ASSIGN,
    INTCON, AND, DIV, SEMICN,
    STRCON, OR, MOD, COMMA,
    MAINTK, FORTK, LSS, LPARENT,
    CONSTTK, GETINTTK, LEQ, RPARENT,
    INTTK, PRINTFTK, GRE, LBRACK,
    BREAKTK, RETURNTK, GEQ, RBRACK,
    CONTINUETK, PLUS, EQL, LBRACE,
    IFTK, MINU, NEQ, RBRACE,
    ELSETK, VOIDTK, MYNULL
};

//enum ParType {
//    CompUnit,
////    Decl,
//    FuncDef,
//    MainFuncDef,
//    ConstDecl,
//    VarDecl,
//    ConstDef,
////    BType,
//    IntIdent,
//    ConstExp,
//    ConstInitVal,
//    VarDef,
//    InitVal,
//    Exp,
//    FuncType,
//    FuncFParams,
//    Block,
//    FuncFParam,
////    BlockItem,
//    Stmt,
//    LVal,
//    Cond,
//    ForStmt,
//    FormatString,
//    AddExp,
//    LOrExp,
//    PrimaryExp,
//    Number,
//    IntConst,
//    UnaryExp,
//    UnaryOp,
//    MulExp,
//    RelExp,
//    EqExp,
//    LAndExp,
//};

class Token {
protected:
    string name = "";
    LexType type = MYNULL;
    int line = 0;

public:
    Token(string name, LexType type, int line) {
        this->name = name;
        this->type = type;
        this->line = line;
    }

    Token(string name, LexType type) {
        this->name = name;
        this->type = type;
    }

    Token() = default;;

    string getName();
    LexType getType();
    int getLine();
};




#endif //LEXER_TOKEN_H
