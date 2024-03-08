#include "Lexer.h"
#include "main.h"
#include <vector>
#include <string>
#include <map>
#include "StrToken.h"

Lexer::Lexer(string src, map<string, LexType> keywords) {
    this->src = src;
    this->curPos = 0;
    this->keywords = keywords;
    this->lineNum = 1;
    this->index = 0;
}


bool Lexer::isKeywords(string str) {
    return keywords.count(str);
}

void Lexer::dealNum(string str) {
    string s;
    char c = str[curPos];
    while (curPos < str.size() && isdigit(c)) {
        s.push_back(c);
        curPos++;
        c = str[curPos];
    }
    Token token(s, INTCON, lineNum);
    srcList.push_back(token);
}

void Lexer::dealAlpha(string str) {
    string s;
    char c = str[curPos];
    while (curPos < str.size() && (isdigit(c) || isalpha(c) || c == '_')) {
        s.push_back(c);
        curPos++;
        c = str[curPos];
    }
    if (isKeywords(s)) {
        Token token(s, keywords[s], lineNum);
        srcList.push_back(token);
    } else {
        Token token(s, IDENFR, lineNum);
        srcList.push_back(token);
    }
}

void Lexer::dealString(string str) {
//    int count = 0;
    curPos++;
    string s;
    s.push_back('"');
    char c = str[curPos];
    while (curPos < str.size() && c != '"') {
        /*if (c == '%') {
            count++;
        }*/
        s.push_back(c);
        curPos++;
        c = str[curPos];
    }
    s.push_back(c);
    Token token(s, STRCON, lineNum);
    srcList.push_back(token);
    curPos++;
}

void Lexer::lexerDeal(string str) {
    char c;
    while (curPos < str.size()) {
        c = str[curPos];
        if (c == '\n') {
            curPos++;
            lineNum++;
        } else if (isspace(c) || c == '\t' || c == '\r') {
            curPos++;
        } else if (isdigit(c)) {
            dealNum(str);
        } else if (isalpha(c) || c == '_') {
            dealAlpha(str);
        } else if (c == '"') {
            dealString(str);
        } else if (c == '!') {
            c = str[++curPos];
            if (c == '=') {
                Token token("!=", NEQ, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                Token token("!", NOT, lineNum);
                srcList.push_back(token);
                //error没写
            }
        } else if (c == '&') {
            c = str[++curPos];
            if (c == '&') {
                Token token("&&", AND, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                //error
            }
        } else if (c == '|') {
            c = str[++curPos];
            if (c == '|') {
                Token token("||", OR, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                //error
            }
        } else if (c == '+') {
            Token token("+", PLUS, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '-') {
            Token token("-", MINU, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '*') {
            Token token("*", MULT, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '/') {
            curPos++;
            string token;
            token += c;
            if (curPos < str.length() && str[curPos] == '/') { //
                // 第二个 /
                c = str[curPos++]; //
                token += c;
                while (curPos < str.length() && str[curPos] != '\n') {
                    // 非换行字符
                    c = str[curPos++];
                    token += c;
                }
                if (curPos < str.length()) { // \n 或 直接结束
                    c = str[curPos++];
                    token += c;
                    lineNum++; // 单行注释末尾的\n
                }
//            lexType = LexType.NOTE;
//            return next();
            } else if (curPos < str.length() && str[curPos] == '*') {
                // /* 跨行注释 用状态机判断
                c = str[curPos++];
                token += c;
                while (curPos < str.length()) {  // 状态转换循环（直至末尾）
                    while (curPos < str.length() && str[curPos] != '*') {
                        // 非*字符 对应状态q5
                        c = str[curPos++];
                        token += c;
                        if (c == '\n')
                            lineNum++; // 多行注释中 每行最后的回车
                    }
                    // *
                    while (curPos < str.length() && str[curPos] == '*') {
                        // *字符 对应状态q6 如果没有转移到q7，则会在循环中转移到q5
                        c = str[curPos++];
                        token += c;
                    }
                    if (curPos < str.length() && str[curPos] == '/') {
                        // /字符 对应状态q7
                        c = str[curPos++];
                        token += c;
                        break;
//        lexType = LexType.NOTE;
//        return next();
                    }
                }
            } else {
                Token token("/", DIV, lineNum);
                srcList.push_back(token);
                //curPos加过了
            }

        } else if (c == '%') {
            Token token("%", MOD, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '<') {
            c = str[++curPos];
            if (c == '=') {
                Token token("<=", LEQ, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                Token token("<", LSS, lineNum);
                srcList.push_back(token);
                //error没写
            }
        } else if (c == '=') {
            c = str[++curPos];
            if (c == '=') {
                Token token("==", EQL, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                Token token("=", ASSIGN, lineNum);
                srcList.push_back(token);
                //error没写
            }
        } else if (c == '>') {
            c = str[++curPos];
            if (c == '=') {
                Token token(">=", GEQ, lineNum);
                srcList.push_back(token);
                curPos++;
            } else {
                Token token(">", GRE, lineNum);
                srcList.push_back(token);
                //error没写
            }
        } else if (c == ';') {
            Token token(";", SEMICN, lineNum);
            srcList.push_back(token);
            curPos++;

        } else if (c == ',') {
            Token token(",", COMMA, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '(') {
            Token token("(", LPARENT, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == ')') {
            Token token(")", RPARENT, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '[') {
            Token token("[", LBRACK, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == ']') {
            Token token("]", RBRACK, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '{') {
            Token token("{", LBRACE, lineNum);
            srcList.push_back(token);
            curPos++;
        } else if (c == '}') {
            Token token("}", RBRACE, lineNum);
            srcList.push_back(token);
            curPos++;
        }
    }
//    it = srcList.begin();
}

vector<Token> Lexer::getSrcList() {
    return srcList;
}

Token Lexer::peek() {
    return srcList[index];
}


bool Lexer::isEnd() {
//    return it==srcList.end();
    return index == srcList.size();
}

void Lexer::next() {
    if (!isEnd())
        index++;
}

int Lexer::getIndex() {
    return index;
}

void Lexer::setRemove(int a) {
    store = a;
}

void Lexer::remove() {
    index = store;
}

int Lexer::getLine() {
    return this->peek().getLine();
}

int Lexer::getPreLine() {
    return srcList[index - 1].getLine();
}

