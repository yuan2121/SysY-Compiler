//
// Created by 86152 on 15/11/2023.
//
#include "Node.h"
#include "Var.h"
#include "FParam.h"
#include "Block.h"
#include "fstream"

using namespace std;

#ifndef ERROR_FUNC_H
#define ERROR_FUNC_H

extern ofstream fout;

class Func : public Node {
public:
    string type;
    Var *var;
    vector<FParam *> *fParams;
    Block *block;
    bool isMain;
    vector<string> *regs = new vector<string>();

    Func(string type1, Var *var1, vector<FParam *> *fParams1, Block *block1, bool isMain1) :
            type(type1), var(var1), fParams(fParams1), block(block1), isMain(isMain1) {

    }

    void out() override {
        if (isMain) {
            fout << "define dso_local i32 @main() {" << endl;
            block->out();
            fout << "}";
        } else {
            IntTable *newTable = new IntTable();               //进入函数创建一个新的作用域
            newTable->setOutTable(intTable);
            intTable = newTable;
            if (type == "int")
                fout << "define dso_local i32 @" << var->op.getName() << "(";
            else
                fout << "define dso_local void @" << var->op.getName() << "(";
            //参数
            vector<int> *params_ir = new vector<int>();
            for (FParam *f : *fParams) {
                regs->push_back(f->genIR());
                params_ir->push_back(f->dimension);
            }
            myparams(regs);
            fout << "){" << endl;
            for (int i = 0; i < fParams->size(); ++i) {
                string name = (*fParams)[i]->getName();
                Reg *reg1 = new Reg();
                int id = reg1->getID();
                if ((*fParams)[i]->dimension == 0) {
                    myalloca(reg1->toString());
                    mystore((*regs)[i], reg1->toString());
                    intTable->addInt(name, *new IntIdent(name, false, id));
                } else if ((*fParams)[i]->dimension == 1) {
                    myalloca1(reg1->toString());
                    mystore1((*regs)[i], reg1->toString());
                    intTable->addInt(name, *new IntIdent(false, name, 1, 0, id, true));
                } else {
                    myalloca1(reg1->toString());
                    mystore1((*regs)[i], reg1->toString());
                    intTable->addInt(name, *new IntIdent(false, name, 2, 0, (*fParams)[i]->exp->cal(), id, true));
                }
            }
            string name = var->op.getName();
            funcTable->addFunc(name, *new FuncIdent(name, type, params_ir));
            block->out();
            if (type == "void")
                fout << "ret void" << endl;
            fout << "}" << endl;
            intTable = intTable->getOutTable();
        };
    }
};

#endif //ERROR_FUNC_H
