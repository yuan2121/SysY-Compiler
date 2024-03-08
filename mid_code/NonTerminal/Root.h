//
// Created by 86152 on 15/11/2023.
//
#include "Decl.h"
#include "Func.h"
#include <vector>
#include "Node.h"

using namespace std;

#ifndef ERROR_ROOT_H
#define ERROR_ROOT_H

class Root : public Node {
private:
    vector<Decl *> *decl;
    vector<Func *> *func;

public:
    Root(vector<Decl *> *decl1, vector<Func *> *func1) {
        decl = decl1;
        func = func1;
    }

    Root() {
        decl = new vector<Decl *>();
        func = new vector<Func *>();
    };

    void out() override {
        fout << "declare i32 @getint()" << endl
             << "declare void @putint(i32)" << endl
             << "declare void @putch(i32)" << endl
             << "declare void @putstr(i8*)" << endl;
        for (Decl *d : *decl) {
            d->out();
        }
        for (Func *f : *func) {
            f->out();
        }
    }

};

#endif //ERROR_ROOT_H
