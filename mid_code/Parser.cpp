//
// Created by 86152 on 6/10/2023.
//

#include "Parser.h"
#include <iostream>
#include "main.h"
#include "Lexer.h"

using namespace std;

extern ofstream fout;

extern void myPrint(LexType type, string str);

Parser::Parser(Lexer &lexer1) : lexer(lexer1) {

}

void Parser::analyse() {
    root->out();
}

void Parser::CompUnit() {
    vector<class Decl*> *decls = new vector<class Decl*>();
    vector<Func*> *funcs = new vector<Func*>();
    while (lexer.getSrcList()[lexer.getIndex() + 2].getName() != "(") {
        decls->push_back(Decl());
    }
    while (lexer.getSrcList()[lexer.getIndex() + 1].getName() != "main") {
        funcs->push_back(FuncDef());
    }
    funcs->push_back(MainFuncDef());
    root = new Root(decls, funcs);
}

Decl *Parser::Decl() {
    if (lexer.peek().getName() == "const") {
        return ConstDecl();
    } else {
        return VarDecl();
    }
}

Decl *Parser::ConstDecl() {
    vector<Def*> *defs = new vector<Def*>();
    lexer.next();//const
    lexer.next();//int
    while (1) {
        defs->push_back(ConstDef());
        if (lexer.peek().getName() == ",") {
            lexer.next();
            continue;
        } else if (lexer.peek().getName() == ";") {
            lexer.next();
            break;
        } else {//myError 灏?
            error();
            break;
        }
    }
    return new class Decl(defs, true);
}

Def *Parser::ConstDef() {
    int count = 0;
    Token token = lexer.peek();
    lexer.next();
    vector<class Exp*> *exps = new vector<class Exp*>();
    class Exp *exp1 = nullptr, *exp2 = nullptr;
    class LVal *lVal = nullptr;
    if (lexer.peek().getName() == "[") {
        lexer.next();//[
        exp1 = ConstExp();
        lexer.next();//]
        count++;
        if (lexer.peek().getName() == "[") {
            lexer.next();//[
            exp2 = ConstExp();
            lexer.next();//]
            count++;
        }
    }
    if (count == 0) {
        lVal = new Var(token);
    } else if (count == 1) {
        lVal = new Array(token, exp1, true);
    } else {
        lVal = new Array(token, exp1, exp2, true);
    }
    lexer.next();//=
    ConstInitVal(exps);
    return new class ConstDef(lVal, exps);
}

void Parser::ConstInitVal(vector<class Exp*> *exps) {
    if (lexer.peek().getName() != "{") {
        exps->push_back(ConstExp());
    } else {
        lexer.next();//{
        if (lexer.peek().getName() != "}") {
            while (1) {
                ConstInitVal(exps);
                if (lexer.peek().getName() == ",") {
                    lexer.next();//,
                    continue;
                } else if (lexer.peek().getName() == "}") {
                    lexer.next();//}
                    break;
                } else;//error;
            }
        } else {
            lexer.next();//}
        }
    }
}

Decl *Parser::VarDecl() {
    vector<Def*> *defs = new vector<Def*>();
    lexer.next();//int
    while (1) {
        defs->push_back(VarDef());
        if (lexer.peek().getName() == ",") {
            lexer.next();//,
            continue;
        } else if (lexer.peek().getName() == ";") {
            lexer.next();//,
            break;
        } else;//error
    }
    return new class Decl(defs, false);
}

Def *Parser::VarDef() {
    int level = 0;
    int count = 0;
    Token token = lexer.peek();
    lexer.next();
    class LVal *lVal = nullptr;
    class Exp *exp1 = nullptr, *exp2 = nullptr;
    vector<vector<class Exp*>*> *exps = new vector<vector<class Exp*>*>();
    if (lexer.peek().getName() == "[") {
        count++;
        lexer.next();//[
        exp1 = ConstExp();
        lexer.next();//]
        if (lexer.peek().getName() == "[") {
            count++;
            lexer.next();//[
            exp2 = ConstExp();
            lexer.next();//]
        }
    }
    if (count == 0) {
        lVal = new Var(token);
    } else if (count == 1) {
        lVal = new Array(token, exp1, false);
    } else {
        lVal = new Array(token, exp1, exp2, false);
    }
    if (lexer.peek().getName() == "=") {
        lexer.next();//=
        InitVal(exps, level);
    }
    return new class VarDef(lVal, exps);
}

void Parser::InitVal(vector<vector<class Exp*>*> *exps, int level) {
    if (lexer.peek().getName() == "{") {
        if (level == 1) {
            exps->push_back(new vector<class Exp*>());
        }
        lexer.next();//{
        if (lexer.peek().getName() == "}") {
            lexer.next();
        } else {
            InitVal(exps, level + 1);
            while (lexer.peek().getName() == ",") {
                lexer.next();
                InitVal(exps, level + 1);
            }
            lexer.next();//}
        }
    } else {
        if (exps->size() == 0) {
            exps->push_back(new vector<class Exp*>());
        }
        (*exps)[exps->size() - 1]->push_back(Exp());//////
    }
}

string Parser::FuncType() {
    if (lexer.peek().getName() == "int") {
        lexer.next();
        return "int";
    } else if (lexer.peek().getName() == "void") {
        lexer.next();
        return "void";
    } else return "error";//error
}

Func *Parser::FuncDef() {
    string funcType = FuncType();
    Var *var = new Var(lexer.peek());
    vector<FParam*> *fParams = new vector<FParam*>();
    class Block *block;
    lexer.next();//var
    lexer.next();//(
    if (lexer.peek().getName() != ")") {
        fParams = FuncFParams();
    }
    lexer.next();//)
    block = Block();
    return new Func(funcType, var, fParams, block, false);
}

Func *Parser::MainFuncDef() {
    lexer.next();//int
    lexer.next();//main
    lexer.next();//(
    lexer.next();//)
    class Block *block = Block();
    return new Func("int", new Var(*(new Token("main", MAINTK))),
                    new vector<FParam*>(), block, true);
}

//void Parser::FuncType() {
//
//}

vector<FParam*> *Parser::FuncFParams() {
    vector<FParam*> *fparams = new vector<FParam*>();
    fparams->push_back(FuncFParam());
    while (lexer.peek().getName() == ",") {
        lexer.next();//,
        fparams->push_back(FuncFParam());
    }
    return fparams;
}

FParam *Parser::FuncFParam() {
    lexer.next();//int
    int count = 0;
    class Exp *exp = nullptr;
    Var *var = new Var(lexer.peek());
    lexer.next();//var
    if (lexer.peek().getName() == "[") {
        count++;
        lexer.next();//[
        lexer.next();//]
        if (lexer.peek().getName() == "[") {
            count++;
            lexer.next();//[
            exp = ConstExp();
            lexer.next();//]
        }
    }
    return new FParam(var, count, exp);
}

Block *Parser::Block() {
    vector<class BlockItem*>* blockItems = new vector<class BlockItem*>();
    lexer.next();//{
    while (lexer.peek().getName() != "}") {
        class BlockItem* bl = BlockItem();
        if (bl != nullptr) {
            blockItems->push_back(bl);
        }
    }
    lexer.next();//}
    return new class Block(blockItems);
}

BlockItem *Parser::BlockItem() {
    if (lexer.peek().getName() == "int" || lexer.peek().getName() == "const") {
        return Decl();
    } else {
        return Stmt();
    }
}

Stmt *Parser::Stmt() {
    if (lexer.peek().getName() == "if") {
        lexer.next();//if
        lexer.next();//(
        OrExp* orExp = Cond();
        lexer.next();//)
        class Stmt* stmt1 = Stmt();
        class Stmt* stmt2 = nullptr;
        if (lexer.peek().getName() == "else") {
            lexer.next();//else
            stmt2 = Stmt();
        }
        return new If(orExp, stmt1, stmt2);
    } else if (lexer.peek().getName() == "{") {
        return Block();
    } else if (lexer.peek().getName() == "for") {
        class ForStmt *stmt1 = nullptr, *stmt2 = nullptr;
        class Stmt* stmt;
        OrExp *orExp = nullptr;
        lexer.next();//for
        lexer.next();//(
        if (lexer.peek().getName() != ";") {
            stmt1 = ForStmt();
        }
        lexer.next();//;
        if (lexer.peek().getName() != ";") {
            orExp = Cond();
        }
        lexer.next();//;
        if (lexer.peek().getName() != ")") {
            stmt2 = ForStmt();
        }
        lexer.next();//)
        stmt = Stmt();
        return new For(stmt1, orExp, stmt2, stmt);
    } else if (lexer.peek().getName() == "break") {
        lexer.next();//break
        lexer.next();//;
        return new Break();
    } else if (lexer.peek().getName() == "continue") {
        lexer.next();//continue
        lexer.next();//;
        return new Continue();
    } else if (lexer.peek().getName() == "return") {
        lexer.next();//return
        class Exp *exp = nullptr;
        if (lexer.peek().getName() != ";") {
            exp = Exp();
        }
        lexer.next();//;
        return new MyReturn(exp);
    } else if (lexer.peek().getName() == "printf") {
        vector<class Exp*>* exps = new vector<class Exp*>();
        lexer.next();//printf
        lexer.next();//(
        Token token = lexer.peek();
        lexer.next();//formatString
        while (lexer.peek().getName() == ",") {
            lexer.next();//,
            exps->push_back(Exp());
        }
        lexer.next();//)
        lexer.next();//;
        return new MyPrintf(token, exps);
    } else if (lexer.peek().getName() == ";") {
        lexer.next();//;
    } else if (lexer.peek().getType() == INTCON ||
               lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!" ||
               lexer.peek().getName() == "(") {
        class Exp* exp = Exp();
        lexer.next();//;
        return exp;
    } else if (lexer.peek().getType() == IDENFR) {
        lexer.setRemove(lexer.getIndex());
        Exp2();
        if (lexer.peek().getName() == ";") {
            lexer.remove();
            class Exp *exp = Exp();
            lexer.next();//;
            return exp;
        } else if (lexer.peek().getName() == "=") {
            lexer.remove();
            class LVal* lVal = LVal();
            if (lVal == nullptr) {
                printf("parser1 line 364");
            }
            lexer.next();//=
            if (lexer.peek().getName() == "getint") {
                lexer.next();//getint
                lexer.next();//(
                lexer.next();//)
                lexer.next();//;
                return new Getint(lVal);
            } else {
                class Exp* exp = Exp();
                lexer.next();//;
                return new Assign(lVal, exp);
            }
        } else;//error
    }
    return nullptr;
}

ForStmt* Parser::ForStmt() {
    class LVal* lVal = LVal();
    lexer.next();//=
    class Exp* exp = Exp();
    return new class ForStmt(lVal, exp);
}

Exp *Parser::Exp() {
    return AddExp();
}

void Parser::Exp2() {
    AddExp2();
}

OrExp *Parser::Cond() {
    return LOrExp();
}

void Parser::Cond2() {
    LOrExp2();
}

LVal *Parser::LVal() {
    Token token = lexer.peek();
    lexer.next();
    class Exp* exp1 = nullptr;
    class Exp* exp2 = nullptr;
    int level = 0;
    if (lexer.peek().getName() == "[") {
        level++;
        lexer.next();//[
        exp1 = Exp();
        lexer.next();//]
        if (lexer.peek().getName() == "[") {
            level++;
            lexer.next();//[
            exp2 = Exp();
            lexer.next();//]
        }
    }
    if (level == 0) {
        return new Var(token);
    } else if (level == 1) {
        return new Array(token, exp1, false);
    } else {
        return new Array(token, exp1, exp2, false);
    }
}

void Parser::LVal2() {
    Ident2();
    while (lexer.peek().getName() == "[") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//[
        Exp2();
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//]
    }
}

Exp *Parser::PrimaryExp() {
    if (lexer.peek().getName() == "(") {
        lexer.next();//(
        class Exp* exp = Exp();
        lexer.next();//)
        return exp;
    } else if (lexer.peek().getType() == INTCON) {
        return Number();
    } else {
        return LVal();
    }
}

void Parser::PrimaryExp2() {
    if (lexer.peek().getName() == "(") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//(
        Exp2();
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//)
    } else if (lexer.peek().getType() == INTCON) {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//number;
    } else {
        LVal2();
    }
}

Exp *Parser::UnaryExp() {
    if (lexer.peek().getType() == IDENFR && lexer.getSrcList()[lexer.getIndex() + 1].getName() == "(") {
        Token token = lexer.peek();
        lexer.next();//name
        lexer.next();//(
        vector<class Exp*> *exps = new vector<class Exp*>();
        if (lexer.peek().getName() != ")") {
            exps = FuncRParams();
        }
        lexer.next();//)
        return new FuncR(token, exps);
    } else if (lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!") {
        Token token = lexer.peek();//UnaryOp();
        lexer.next();
        class Exp* exp = UnaryExp();
        return new class UnaryExp(token, exp);
    } else {
        return PrimaryExp();
    }
}

void Parser::UnaryExp2() {
    if (lexer.peek().getType() == IDENFR && lexer.getSrcList()[lexer.getIndex() + 1].getName() == "(") {
        Ident2();
        lexer.next();//(
        if (lexer.peek().getName() != ")") {
            FuncRParams2();
        }
        lexer.next();//)
    } else if (lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!") {
        // myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//+-!
        UnaryExp2();
    } else {
        PrimaryExp2();
    }
}

//Token Parser::UnaryOp() {
//    lexer.next();//+-!
//}

vector<class Exp*>* Parser::FuncRParams() {
    vector<class Exp*>* exps = new vector<class Exp*>();
    exps->push_back(Exp());
    while (lexer.peek().getName() == ",") {
        lexer.next();//,
        exps->push_back(Exp());
    }
    return exps;
}

void Parser::FuncRParams2() {
    Exp2();
    while (lexer.peek().getName() == ",") {
        lexer.next();
        Exp2();
    }
}

Exp *Parser::MulExp() {
    class Exp* exp1 = UnaryExp();
    while (lexer.peek().getName() == "*" ||
            lexer.peek().getName() == "/" ||
            lexer.peek().getName() == "%") {
        Token token = lexer.peek();
        lexer.next();//*/%
        class Exp* exp2 = UnaryExp();
        exp1 = new CalExp(token, exp1, exp2);
    }
    return exp1;
}

void Parser::MulExp2() {
    UnaryExp2();
    while (lexer.peek().getName() == "*" ||
           lexer.peek().getName() == "/" ||
           lexer.peek().getName() == "%") {
        lexer.next();
        UnaryExp2();
    }
}

Exp *Parser::AddExp() {
    class Exp* exp1 = MulExp();

    while (lexer.peek().getName() == "+" || lexer.peek().getName() == "-") {
        Token token = lexer.peek();
        lexer.next();//+-
        class Exp* exp2 = MulExp();
        exp1 = new CalExp(token, exp1, exp2);
    }
    return exp1;
}

void Parser::AddExp2() {
    MulExp2();
    while (lexer.peek().getName() == "+" ||
           lexer.peek().getName() == "-") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//+=
        MulExp2();
    }
}

Exp *Parser::RelExp() {
    class Exp* exp1 = AddExp();
    while (lexer.peek().getName() == ">" ||
            lexer.peek().getName() == "<" ||
            lexer.peek().getName() == ">=" ||
            lexer.peek().getName() == "<=") {
        Token token = lexer.peek();
        lexer.next();//> < >= <=
        class Exp* exp2 = AddExp();
        exp1 = new LogExp(token, exp1, exp2);
    }
    return exp1;
}

void Parser::RelExp2() {
    AddExp();
    while (lexer.peek().getName() == ">" ||
           lexer.peek().getName() == "<" ||
           lexer.peek().getName() == ">=" ||
           lexer.peek().getName() == "<=") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//> < >= <=
        AddExp2();
    }
}

Exp *Parser::EqExp() {
    class Exp* exp1 = RelExp();
    while (lexer.peek().getName() == "==" ||
            lexer.peek().getName() == "!=") {
        Token token = lexer.peek();
        lexer.next();//== !=
        class Exp* exp2 = RelExp();
        exp1 = new LogExp(token, exp1, exp2);
    }
    return exp1;
}

void Parser::EqExp2() {
    RelExp2();
    while (lexer.peek().getName() == "==" ||
           lexer.peek().getName() == "!=") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//== !=
        RelExp2();
    }
}

AndExp *Parser::LAndExp() {
    vector<class Exp*>* exps = new vector<class Exp*>();
    exps->push_back(EqExp());
    while (lexer.peek().getName() == "&&") {
        lexer.next();//&&
        exps->push_back(EqExp());
    }
    return new AndExp(exps);
}

void Parser::LAndExp2() {
    EqExp2();
    while (lexer.peek().getName() == "&&") {
//        myPrint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//&&
        EqExp2();
    }
}

OrExp *Parser::LOrExp() {
    vector<AndExp*>* ands = new vector<AndExp*>();
    ands->push_back(LAndExp());
    while (lexer.peek().getName() == "||") {
        lexer.next();//||
        ands->push_back(LAndExp());
    }
    return new OrExp(ands);
}

void Parser::LOrExp2() {
    LAndExp2();
    while (lexer.peek().getName() == "||") {
        lexer.next();//||
        LAndExp2();
    }
}

Exp *Parser::ConstExp() {
    return AddExp();
}

void Parser::ConstExp2() {
    AddExp2();
}

void Parser::Ident2() {
    lexer.next();
}


Exp *Parser::Number() {
    Token token = lexer.peek();
    lexer.next();
    return new class Number(token);
}