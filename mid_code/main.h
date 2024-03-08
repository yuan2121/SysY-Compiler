#include <string>
#include "Token.h"

using namespace std;

#ifndef LEXER_MAIN_H
#define LEXER_MAIN_H

void initStream();
void closeStream();
void read(string &str);
void initKeywords();
void myPrint(LexType type, string str);
void closeStream();
void myError(int a, string str);
void mycout(string str);

#endif //LEXER_MAIN_H


