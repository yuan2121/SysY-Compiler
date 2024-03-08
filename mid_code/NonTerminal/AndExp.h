//
// Created by 86152 on 15/11/2023.
//
#include "Node.h"
#include <vector>
#include "Exp.h"
#include "../Reg.h"
#include "LogExp.h"

using namespace std;
#ifndef ERROR_AND_H
#define ERROR_AND_H


class AndExp : public Node {
public:
    vector<Exp *> *exps;
//    static int count;
//    int num;
    int label;

    explicit AndExp(vector<Exp *> *exps1) : exps(exps1) {
//        num = ++count;
    }

    void out(int n) {
        label = ++labels;
        for (Exp *e : *exps) {
            int label1 = ++labels;
            string id;
            if (e->op.getName() != "==" && e->op.getName() != "!=" &&
                e->op.getName() != ">" && e->op.getName() != "<" &&
                e->op.getName() != "<=" && e->op.getName() != ">=") {
                Reg *reg = new Reg();
                id = reg->toString();

                mycmp(id, "!=", "0", e->genIR());
            } else {
//                id = e->genIR();
                Reg *reg = new Reg();
                id = reg->toString();
                mycmp(id, "!=", "0", e->genIR());
            }
            mybr(id, "%l" + to_string(label1), "%l" + to_string(label));
            mylabel("l" + to_string(label1));
        }
        mybr("%l" + to_string(n));
        mylabel("l" + to_string(label));
    }
};


#endif //ERROR_AND_H
