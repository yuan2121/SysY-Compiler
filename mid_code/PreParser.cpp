//
// Created by 86152 on 6/10/2023.
//

#include "PreParser.h"
#include "main.h"
#include "Lexer.h"
#include "IntTable.h"
#include <algorithm>
#include <string>

using namespace std;

extern int haveError;

extern void myError(int a, string str);

extern void mycout(string str);

PreParser::PreParser(Lexer &lexer1) : lexer(lexer1) {
}

void PreParser::CompUnit() {
    while (lexer.getSrcList()[lexer.getIndex() + 2].getName() != "(") {
        Decl();
    }
    while (lexer.getSrcList()[lexer.getIndex() + 1].getName() != "main") {
        FuncDef();
    }
    MainFuncDef();
    lexer.resetIndex();
}

void PreParser::Decl() {
    if (lexer.peek().getName() == "const") {
        ConstDecl();
    } else {
        VarDecl();
    }
}

void PreParser::ConstDecl() {
    lexer.next();//const
    lexer.next();//int
    while (1) {
        ConstDef();
        if (lexer.peek().getName() == ",") {
            lexer.next();
            continue;
        } else if (lexer.peek().getName() == ";") {
            lexer.next();
            break;
        } else {//myError 少;
            myError(lexer.getPreLine(), "i");
            break;
        }
    }
}

void PreParser::ConstDef() {
    string name = lexer.peek().getName();
    lexer.next();//ident
    int line = lexer.peek().getLine();
    int num = 0;
    while (lexer.peek().getName() == "[") {
        num++;
        lexer.next();
        ConstExp();
        if (lexer.peek().getName() != "]") {
            myError(lexer.getPreLine(), "k");
        } else {
            lexer.next();
        }
    }
    lexer.next();//=
    ConstInitVal();
    if (intTable->contain(name) || (funcTable->contain(name) && intTable->getOutTable() == nullptr)) {
        myError(lexer.getPreLine(), "b");
    } else {
        IntIdent ident(name, line, num, true);
        intTable->addInt(name, ident);
    }
//    //fout << "<ConstDef>" << endl;
}

void PreParser::ConstInitVal() {
    if (lexer.peek().getName() != "{") {
        ConstExp();
    } else {
        lexer.next();
        if (lexer.peek().getName() != "}") {
            while (1) {
                ConstInitVal();
                if (lexer.peek().getName() == ",") {
                    lexer.next();
                    continue;
                } else if (lexer.peek().getName() == "}") {
                    lexer.next();
                    break;
                } else;//myError;
            }
        } else {
            lexer.next();
        }
    }
//    //fout << "<ConstInitVal>" << endl;
}

void PreParser::VarDecl() {
    lexer.next();
    while (1) {
        VarDef();
        if (lexer.peek().getName() == ",") {
            lexer.next();
            continue;
        } else if (lexer.peek().getName() == ";") {
            lexer.next();
            break;
        } else {//myError 少;
            myError(lexer.getPreLine(), "i");
            break;
        }
    }
    //fout << "<VarDecl>" << endl;
}

void PreParser::VarDef() {
    string name = lexer.peek().getName();
    lexer.next();//ident
    int line = lexer.peek().getLine();
    int num = 0;
    while (lexer.peek().getName() == "[") {
        num++;
        lexer.next();
        ConstExp();
        if (lexer.peek().getName() != "]") {
            myError(lexer.getPreLine(), "k");
        } else {
            lexer.next();
        }
    }

    if (lexer.peek().getName() == "=") {
        lexer.next();
        InitVal();
    }
    if (intTable->contain(name) || (funcTable->contain(name) && intTable->getOutTable() == nullptr)) {
        myError(lexer.getPreLine(), "b");
    } else {
        IntIdent intIdent(name, line, num, false);
        intTable->addInt(name, intIdent);
    }
//    //fout << "<VarDef>" << endl;
}

void PreParser::InitVal() {
    if (lexer.peek().getName() != "{") {
        Exp();
    } else {
        lexer.next();
        if (lexer.peek().getName() != "}") {
            while (1) {
                InitVal();
                if (lexer.peek().getName() == ",") {
                    lexer.next();
                    continue;
                } else if (lexer.peek().getName() == "}") {
                    lexer.next();
                    break;
                } else;//myError;
            }
        } else {
            lexer.next();
        }
    }
//    //fout << "<InitVal>" << endl;
}

string PreParser::FuncType() {
    if (lexer.peek().getName() == "int") {
        return "int";
    } else if (lexer.peek().getName() == "void") {
        return "void";
    }
    return "error";
}

void PreParser::FuncDef() {
    IntTable *newTable = new IntTable();               //进入函数创建一个新的作用域
    newTable->setOutTable(intTable);
    intTable = newTable;
    funcType = FuncType();
    string type = funcType;
    lexer.next();//type
    string name = lexer.peek().getName();
    int line = lexer.getLine();
    if (funcTable->contain(name) || intTable->outContain(name)) {
        myError(lexer.getLine(), "b");
    }
    lexer.next();//ident
    lexer.next();//(
    vector<IntIdent> *params = new vector<IntIdent>();
    if (lexer.peek().getName() == "{") {
        myError(lexer.getPreLine(), "j");          //j 少)
    } else if (lexer.peek().getName() == ")") {
        lexer.next();
    } else {
        *params = FuncFParams();
        if (lexer.peek().getName() == ")") {
            lexer.next();//)
        } else {
            myError(lexer.getPreLine(), "j");           //j 少)
        }
    }
    FuncIdent funcIdent(name, line, *params, type);
    funcTable->addFunc(name, funcIdent);
    infunc = 1;
//    funcDefHaveReturn = false;
    int returnLine = Block();
    if (type == "int" && !haveReturn) {
        myError(returnLine, "g");
    }
//    //fout << "<FuncDef>" << endl;
}

void PreParser::MainFuncDef() {
    lexer.next();//int
    lexer.next();//main
    lexer.next();//(
    if (lexer.peek().getName() == ")") {
        lexer.next();//)
    } else {
        myError(lexer.getPreLine(), "j");
    }
    funcType = "int";
    int line = Block();
    if (!haveReturn) {
        myError(line, "g");
    }
//    //fout << "<MainFuncDef>" << endl;
}

//void PreParser::FuncType() {
//
//}

vector<IntIdent> PreParser::FuncFParams() {
    vector<IntIdent> *params = new vector<IntIdent>();
    params->push_back(*FuncFParam());
    while (lexer.peek().getName() == ",") {
        lexer.next();//,
        params->push_back(*FuncFParam());
//        FuncFParam();
    }
//    //fout << "<FuncFParams>" << endl;
    return *params;
}

IntIdent *PreParser::FuncFParam() {
    lexer.next();//int
    int line = lexer.getLine();
    int num = 0;
    string name = lexer.peek().getName();
    if (intTable->contain(name)) {                          //错误处理b型
        myError(line, "b");
    }
    lexer.next();//ident
    if (lexer.peek().getName() == "[") {
        lexer.next();//[
        if (lexer.peek().getName() == "]") {
            lexer.next();//]
        } else {
            myError(lexer.getPreLine(), "k");
        }
        num++;
        if (lexer.peek().getName() == "[") {
            lexer.next();//[
            ConstExp();
            if (lexer.peek().getName() == "]") {
                lexer.next();//]
            } else {
                myError(lexer.getPreLine(), "k");
            }
            num++;
        }
    }
    IntIdent *ident = new IntIdent(name, line, num, false);
//    //fout << "<FuncFParam>" << endl;
    intTable->addInt(name, *ident);
    return ident;
}

int PreParser::Block() {
    int line;
    lexer.next();//{
    if (lexer.peek().getName() == "}") {
        haveReturn = false;
        line = lexer.getLine();
        lexer.next();

        if (infunc) {
            infunc = 0;
            intTable = intTable->getOutTable();
        }
    } else {
        if (infunc) {
            infunc = !infunc;
        } else {
            IntTable *newTable = new IntTable();               //进入函数创建一个新的作用域
            newTable->setOutTable(intTable);
            intTable = newTable;
        }
        haveReturn = false;
        BlockItem();
        while (lexer.peek().getName() != "}") {
            haveReturn = false;
            BlockItem();
        }
        line = lexer.getLine();
        lexer.next();//}
        intTable = intTable->getOutTable();
    }
//    //fout << "<Block>" << endl;
    return line;
}

void PreParser::BlockItem() {
    if (lexer.peek().getName() == "int" || lexer.peek().getName() == "const") {
        Decl();
    } else {
        Stmt();
    }
}

void PreParser::Stmt() {
    if (lexer.peek().getName() == "if") {
        inCon = true;
        lexer.next();//if
        lexer.next();//(
        Cond();
        if (lexer.peek().getName() == ")") {
            lexer.next();
        } else {
            myError(lexer.getPreLine(), "j");
        }
        Stmt();
        if (lexer.peek().getName() == "else") {
            lexer.next();//else
            Stmt();
        }
        inCon = false;
    } else if (lexer.peek().getName() == "{") {
        inCon = true;
        Block();
        inCon = false;
    } else if (lexer.peek().getName() == "for") {
        inCon = true;
        lexer.next();//for
        lexer.next();//(
        if (lexer.peek().getName() != ";") {
            ForStmt();
        }
        lexer.next();//;
        if (lexer.peek().getName() != ";") {
            Cond();
        }
        lexer.next();//;
        if (lexer.peek().getName() != ")") {
            ForStmt();
        }
        lexer.next();//)
        addCir();
        Stmt();
        subCir();
        inCon = false;
    } else if (lexer.peek().getName() == "break") {
        if (circleNum == 0) {
            myError(lexer.getLine(), "m");
        }
        lexer.next();//break
        if (lexer.peek().getName() == ";") {
            lexer.next();
        } else {
            myError(lexer.getPreLine(), "i");
        }
    } else if (lexer.peek().getName() == "continue") {
        if (circleNum == 0) {
            myError(lexer.getLine(), "m");
        }
        lexer.next();//continue
        if (lexer.peek().getName() == ";") {
            lexer.next();
        } else {
            myError(lexer.getPreLine(), "i");
        }
    } else if (lexer.peek().getName() == "return") {
        if (!inCon) {
            haveReturn = true;
        }
        int line = lexer.getLine();
        lexer.next();//return
        if (lexer.peek().getName() == ";") {
            lexer.next();//;
        } else if (isExp(lexer.peek())) {
            if (funcType == "void") {
                myError(line, "f");
            }
            Exp();
            if (lexer.peek().getName() == ";") {
                lexer.next();//;
            } else {
                myError(lexer.getPreLine(), "i");
            }
        } else {//int
            myError(line, "i");
        }
    } else if (lexer.peek().getName() == "printf") {
        int line = lexer.getLine();
        lexer.next();//printf
        lexer.next();//(
//        FormatString();
        string str = lexer.peek().getName();
        lexer.next();//formatstring
        int count1 = 0;
        for (int i = 1; i < str.size() - 1; ++i) {
            if (str[i] == '\\') {
                if (str[i + 1] != 'n') {
                    myError(line, "a");
                    break;
                }
            } else if (str[i] == '%') {
                if (str[i + 1] == 'd') {
                    count1++;
                } else {
                    myError(line, "a");
                    break;
                }
            } else if (str[i] == 32 || str[i] == 33 || (str[i] >= 40 && str[i] <= 126)) {
                continue;
            } else {
                myError(line, "a");
                break;
            }
        }
        int countExp = 0;
        while (lexer.peek().getName() == ",") {
            lexer.next();//,
            Exp();
            countExp++;
        }
        if (count1 != countExp) {
            myError(line, "l");
        }
        if (lexer.peek().getName() == ")") {
            lexer.next();//)
        } else {
            myError(lexer.getPreLine(), "j");
        }
        if (lexer.peek().getName() == ";") {
            lexer.next();//;
        } else {
            myError(lexer.getPreLine(), "i");
        }
    } else if (lexer.peek().getName() == ";") {
        lexer.next();//;
    } else if (lexer.peek().getType() == INTCON ||
               lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!" ||
               lexer.peek().getName() == "(") {
        Exp();
        lexer.next();//;
    } else if (lexer.peek().getType() == IDENFR) {
        lexer.setRemove(lexer.getIndex());
        Exp2();
        if (lexer.peek().getName() == ";") {
            lexer.remove();
            Exp();
            lexer.next();//;
        } else if (lexer.peek().getName() == "=") {
            lexer.remove();
            IntIdent ident = LVal();
            if (ident.isConst()) {
                myError(ident.getLine(), "h");
            }
//            //fout << "<LVal>" << endl;
            lexer.next();//=
            if (lexer.peek().getName() == "getint") {
                lexer.next();//getint
                lexer.next();//(
                if (lexer.peek().getName() == ")") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "j");
                }
                if (lexer.peek().getName() == ";") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "i");
                }
            } else {
                Exp();
                if (lexer.peek().getName() == ";") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "i");
                }
            }
        } else {
            myError(lexer.getPreLine(), "i");
        }
    }
//    //fout << "<Stmt>" << endl;
}


void PreParser::ForStmt() {
    IntIdent ident = LVal();
    if (ident.isConst()) {
        myError(ident.getLine(), "h");
    }
    lexer.next();//=
    Exp();
}

void PreParser::Exp() {
    AddExp();
}

void PreParser::Exp2() {
    AddExp2();
}

void PreParser::Cond() {
    LOrExp();
    //fout << "<Cond>" << endl;
}

void PreParser::Cond2() {
    LOrExp2();
}

IntIdent PreParser::LVal() {
    IntIdent *ident = new IntIdent();
    string name = lexer.peek().getName();
    int line = lexer.getLine();
    if (!intTable->outContain(name)) {
        myError(line, "c");
    } else {
        *ident = intTable->outGet(name);
    }
    int dimension = ident->getDimension();
    ident->setLine(line);
    lexer.next();//ident
    while (lexer.peek().getName() == "[") {
        dimension--;
        lexer.next();//[
        Exp();
        if (lexer.peek().getName() == "]") {
            lexer.next();
        } else {
            myError(lexer.getPreLine(), "k");                //k型错误
        }
    }
    ident->setDimension(dimension);
    return *ident;
//    //fout << "<LVal>" << endl;
}

void PreParser::LVal2() {
    Ident2();
    while (lexer.peek().getName() == "[") {
        lexer.next();//[
        Exp2();
        if (lexer.peek().getName() == "]") {
            lexer.next();
        }
    }
}

void PreParser::PrimaryExp() {
    if (lexer.peek().getName() == "(") {
        lexer.next();//(
        Exp();
        if (lexer.peek().getName() == ")") {
            lexer.next();
        } else {
            myError(lexer.getPreLine(), "j");
        }
    } else if (lexer.peek().getType() == INTCON) {
        Number();
        if (isParam) {
            arrayLevel = 0;
        }
    } else {
        IntIdent ident = LVal();
        if (isParam) {
            arrayLevel = ident.getDimension();
        }
    }
//    //fout << "<PrimaryExp>" << endl;
}

void PreParser::PrimaryExp2() {
    if (lexer.peek().getName() == "(") {
        lexer.next();//(
        Exp2();
        if (lexer.peek().getName() == ")") {
            lexer.next();
        }
    } else if (lexer.peek().getType() == INTCON) {
        lexer.next();//number;
    } else {
        LVal2();
    }
}

void PreParser::UnaryExp() {
    if (lexer.peek().getType() == IDENFR && lexer.getSrcList()[lexer.getIndex() + 1].getName() == "(") {
        string name = lexer.peek().getName();
        int line = lexer.getLine();
        lexer.next();//ident
        lexer.next();//(
        if (funcTable->contain(name)) {
            FuncIdent ident = funcTable->get(name);
            if (isParam) {
                arrayLevel = (ident.getType() == "int") ? 0 : -1;
            }
            vector<IntIdent> fParams = ident.getParams();
            vector<int> *rParams = new vector<int>();
            if (isExp(lexer.peek())) {
                *rParams = FuncRParams();
                if (fParams.size() != rParams->size()) {
                    myError(line, "d");
                } else {
                    for (int i = 0; i < fParams.size(); ++i) {
                        if (fParams[i].getDimension() != (*rParams)[i]) {
                            myError(line, "e");
                            break;
                        }
                    }
                }
                if (lexer.peek().getName() == ")") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "j");
                }
            } else {
                if (fParams.size() != rParams->size()) {
                    myError(line, "d");
                }
                if (lexer.peek().getName() == ")") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "j");
                }
            }

        } else {
            myError(line, "c");
            if (isExp(lexer.peek())) {
                FuncRParams();
                if (lexer.peek().getName() == ")") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "j");
                }
            } else {
                if (lexer.peek().getName() == ")") {
                    lexer.next();
                } else {
                    myError(lexer.getPreLine(), "j");
                }
            }
        }
    } else if (lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!") {
        UnaryOp();
        UnaryExp();
    } else {
        PrimaryExp();
    }
//    //fout << "<UnaryExp>" << endl;
}

void PreParser::UnaryExp2() {
    if (lexer.peek().getType() == IDENFR && lexer.getSrcList()[lexer.getIndex() + 1].getName() == "(") {
        Ident2();
        lexer.next();//(
        if (lexer.peek().getName() == ";") {

        } else if (lexer.peek().getName() != ")") {
            FuncRParams2();
            if (lexer.peek().getName() == ")")
                lexer.next();//)
        } else {
            lexer.next();
        }
    } else if (lexer.peek().getName() == "+" ||
               lexer.peek().getName() == "-" ||
               lexer.peek().getName() == "!") {
        // //myprint(lexer.peek().getType(), lexer.peek().getName());
        lexer.next();//+-!
        UnaryExp2();
    } else {
        PrimaryExp2();
    }
//    //fout << "<UnaryExp>" << endl;
}

void PreParser::UnaryOp() {
    //myprint(lexer.peek().getType(), lexer.peek().getName());
    lexer.next();//+-!
    //fout << "<UnaryOp>" << endl;
}

vector<int> PreParser::FuncRParams() {
    int level = arrayLevel;
    vector<int> dimensions;
    isParam = 1;
    Exp();
    isParam = 0;
    dimensions.push_back(arrayLevel);
    int n = 1;
    while (lexer.peek().getName() == ",") {
        lexer.next();//,
        isParam = 1;
        Exp();
        isParam = 0;
        dimensions.push_back(arrayLevel);
    }
//    //fout << "<FuncRParams>" << endl;
    arrayLevel = level;
    return dimensions;
}

void PreParser::FuncRParams2() {
    Exp2();
    while (lexer.peek().getName() == ",") {
        lexer.next();
        Exp2();
    }
}

void PreParser::MulExp() {
    UnaryExp();
    while (lexer.peek().getName() == "*" ||
           lexer.peek().getName() == "/" ||
           lexer.peek().getName() == "%") {
        //fout << "<MulExp>" << endl;
        lexer.next();//*/%
        UnaryExp();
    }
//    //fout << "<MulExp>" << endl;
}

void PreParser::MulExp2() {
    UnaryExp2();
    while (lexer.peek().getName() == "*" ||
           lexer.peek().getName() == "/" ||
           lexer.peek().getName() == "%") {
        lexer.next();
        UnaryExp2();
    }
}

void PreParser::AddExp() {
    MulExp();
    while (lexer.peek().getName() == "+" ||
           lexer.peek().getName() == "-") {
        //fout << "<AddExp>" << endl;
        lexer.next();//+-
        MulExp();
    }
//    //fout << "<AddExp>" << endl;
}

void PreParser::AddExp2() {
    MulExp2();
    while (lexer.peek().getName() == "+" ||
           lexer.peek().getName() == "-") {
        lexer.next();//+=
        MulExp2();
    }
}

void PreParser::RelExp() {
    AddExp();
    while (lexer.peek().getName() == ">" ||
           lexer.peek().getName() == "<" ||
           lexer.peek().getName() == ">=" ||
           lexer.peek().getName() == "<=") {
//        //fout << "<RelExp>" << endl;
        lexer.next();//> < >= <=
        AddExp();
    }
//    //fout << "<RelExp>" << endl;
}

void PreParser::RelExp2() {
    AddExp();
    while (lexer.peek().getName() == ">" ||
           lexer.peek().getName() == "<" ||
           lexer.peek().getName() == ">=" ||
           lexer.peek().getName() == "<=") {
        lexer.next();//> < >= <=
        AddExp2();
    }
}

void PreParser::EqExp() {
    RelExp();
    while (lexer.peek().getName() == "==" ||
           lexer.peek().getName() == "!=") {
//        //fout << "<EqExp>" << endl;
        lexer.next();//== !=
        RelExp();
    }
//    //fout << "<EqExp>" << endl;
}

void PreParser::EqExp2() {
    RelExp2();
    while (lexer.peek().getName() == "==" ||
           lexer.peek().getName() == "!=") {
        lexer.next();//== !=
        RelExp2();
    }
}

void PreParser::LAndExp() {
    EqExp();
    while (lexer.peek().getName() == "&&") {
        //fout << "<LAndExp>" << endl;
        lexer.next();//&&
        EqExp();
    }
//    //fout << "<LAndExp>" << endl;
}

void PreParser::LAndExp2() {
    EqExp2();
    while (lexer.peek().getName() == "&&") {
        lexer.next();//&&
        EqExp2();
    }
}

void PreParser::LOrExp() {
    LAndExp();
    while (lexer.peek().getName() == "||") {
//        //fout << "<LOrExp>" << endl;
        lexer.next();//||
        LAndExp();
    }
//    //fout << "<LOrExp>" << endl;
}

void PreParser::LOrExp2() {
    LAndExp2();
    while (lexer.peek().getName() == "||") {
        lexer.next();//||
        LAndExp2();
    }
}

void PreParser::ConstExp() {
    AddExp();
//    //fout << "<ConstExp>" << endl;
}

void PreParser::ConstExp2() {
    AddExp2();
}

//string PreParser::IntIdent() {//没有next
//    return lexer.peek().getName();
//}

//string PreParser::FuncIdent() {//没有next
//    if (funcTable->contain(lexer.peek().getName())) {
//        myError(lexer.getLine(), "b");
//    }
//    return lexer.peek().getName();
//}

void PreParser::Ident2() {
    lexer.next();//ident
}

void PreParser::FormatString() {
    lexer.next();
}

void PreParser::Number() {
    lexer.next();
//    //fout << "<Number>" << endl;
}
//
//void PreParser::mymyError(int a, string str) {
//    fout << a << " " << str << endl;
//}