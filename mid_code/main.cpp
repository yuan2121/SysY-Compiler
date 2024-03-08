#include <iostream>
#include <map>
#include <string>
#include "Lexer.h"
#include "main.h"
#include "Token.h"
#include "PreParser.h"
#include "Parser.h"

using namespace std;

int haveError = 0;
string src;
ifstream fin;
ofstream fout,fout_error;
map<string, LexType> keywords;

int main() {
    initKeywords();
    initStream();
    read(src);
    Lexer lexer(src, keywords);
    lexer.lexerDeal(src);
    PreParser preParser(lexer);
    preParser.CompUnit();
    if (haveError == 0) {
        Parser parser(lexer);
        parser.CompUnit();
        parser.analyse();
    }
    closeStream();
    return 0;
}

void initKeywords() {
    keywords["main"] = MAINTK;
    keywords["const"] = CONSTTK;
    keywords["int"] = INTTK;
    keywords["break"] = BREAKTK;
    keywords["continue"] = CONTINUETK;
    keywords["if"] = IFTK;
    keywords["else"] = ELSETK;
    keywords["for"] = FORTK;
    keywords["getint"] = GETINTTK;
    keywords["printf"] = PRINTFTK;
    keywords["return"] = RETURNTK;
    keywords["void"] = VOIDTK;
}

void initStream() {
    fin.open("testfile.txt");
    if (!fin.is_open()) {
        printf("fin failed\n");
    }
    fout.open("llvm_ir.txt");
    if (!fout.is_open()) {
        printf("fout failed\n");
    }
    fout_error.open("error.txt");
    if (!fout.is_open()) {
        printf("fout_error failed\n");
    }
}

void read(string &str) {
    string line;
    while (getline(fin, line)) {
        str += line + '\n';
    }
    fin.close();
}

void closeStream() {
    fout.close();
    fout_error.close();
}

extern void mycout(string str) {
    fout << str << endl;
}


extern void myError(int a, string str) {
    fout_error << a << " " << str << endl;
    haveError++;
}

extern void myPrint(LexType type, string str) {
    switch (type) {
        case IDENFR:
            fout << "IDENFR " << str << endl;
            break;
        case INTCON:
            fout << "INTCON " << str << endl;
            break;
        case STRCON:
            fout << "STRCON " << str << endl;
            break;
        case MAINTK:
            fout << "MAINTK " << str << endl;
            break;
        case CONSTTK:
            fout << "CONSTTK " << str << endl;
            break;
        case INTTK:
            fout << "INTTK " << str << endl;
            break;
        case BREAKTK:
            fout << "BREAKTK " << str << endl;
            break;
        case CONTINUETK:
            fout << "CONTINUETK " << str << endl;
            break;
        case IFTK:
            fout << "IFTK " << str << endl;
            break;
        case ELSETK:
            fout << "ELSETK " << str << endl;
            break;
        case NOT:
            fout << "NOT " << str << endl;
            break;
        case AND:
            fout << "AND " << str << endl;
            break;
        case OR:
            fout << "OR " << str << endl;
            break;
        case FORTK:
            fout << "FORTK " << str << endl;
            break;
        case GETINTTK:
            fout << "GETINTTK " << str << endl;
            break;
        case PRINTFTK:
            fout << "PRINTFTK " << str << endl;
            break;
        case RETURNTK:
            fout << "RETURNTK " << str << endl;
            break;
        case PLUS:
            fout << "PLUS " << str << endl;
            break;
        case MINU:
            fout << "MINU " << str << endl;
            break;
        case VOIDTK:
            fout << "VOIDTK " << str << endl;
            break;
        case MULT:
            fout << "MULT " << str << endl;
            break;
        case DIV:
            fout << "DIV " << str << endl;
            break;
        case MOD:
            fout << "MOD " << str << endl;
            break;
        case LSS:
            fout << "LSS " << str << endl;
            break;
        case LEQ:
            fout << "LEQ " << str << endl;
            break;
        case GRE:
            fout << "GRE " << str << endl;
            break;
        case GEQ:
            fout << "GEQ " << str << endl;
            break;
        case EQL:
            fout << "EQL " << str << endl;
            break;
        case NEQ:
            fout << "NEQ " << str << endl;
            break;
        case RBRACE:
            fout << "RBRACE " << str << endl;
            break;
        case ASSIGN:
            fout << "ASSIGN " << str << endl;
            break;
        case SEMICN:
            fout << "SEMICN " << str << endl;
            break;
        case COMMA:
            fout << "COMMA " << str << endl;
            break;
        case LPARENT:
            fout << "LPARENT " << str << endl;
            break;
        case RPARENT:
            fout << "RPARENT " << str << endl;
            break;
        case LBRACK:
            fout << "LBRACK " << str << endl;
            break;
        case RBRACK:
            fout << "RBRACK " << str << endl;
            break;
        case LBRACE:
            fout << "LBRACE " << str << endl;
            break;
    }
}
