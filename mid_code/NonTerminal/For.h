//
// Created by 86152 on 18/11/2023.
//
#include "Stmt.h"
#include "ForStmt.h"
#include "OrExp.h"

using namespace std;

#ifndef MID_CODE_FOR_H
#define MID_CODE_FOR_H


class For : public Stmt {
public:
    ForStmt *forStmt1 = nullptr;
    ForStmt *forStmt2 = nullptr;
    OrExp *orExp = nullptr;
    Stmt *stmt;
    int label;

    void out() override {
        label = ++labels;
        myStack.push(label);
        if (forStmt1 != nullptr)
            forStmt1->out();
        mybr("%forbegin" + to_string(label));
        mylabel("forbegin" + to_string(label));
        if (orExp != nullptr)
            orExp->out(label, 1);
        if (stmt != nullptr) {
            stmt->out();
        }
        mybr("%fori" + to_string(label));
        mylabel("fori" + to_string(label));
        if (forStmt2 != nullptr) {
            forStmt2->out();
        }
        mybr("%forbegin" + to_string(label));
        mylabel("forend" + to_string(label));
        myStack.pop();
    }

    For(Stmt *stmt) {
        this->stmt = stmt;
    }

    For(ForStmt *stmt1, OrExp *orExp, ForStmt *stmt2, Stmt *stmt) {
        this->stmt = stmt;
        this->forStmt1 = stmt1;
        this->forStmt2 = stmt2;
        this->orExp = orExp;
    }

    For(OrExp *orExp, ForStmt *stmt2, Stmt *stmt) {
        this->stmt = stmt;
        this->forStmt2 = stmt2;
        this->orExp = orExp;
    }

    For(ForStmt *stmt1, ForStmt *stmt2, Stmt *stmt) {
        this->stmt = stmt;
        this->forStmt1 = stmt1;
        this->forStmt2 = stmt2;
        this->orExp = orExp;
    }

    For(ForStmt *stmt1, OrExp *orExp, Stmt *stmt) {
        this->stmt = stmt;
        this->forStmt1 = stmt1;
        this->orExp = orExp;
    }

    For(OrExp *orExp, Stmt *stmt) {
        this->stmt = stmt;
        this->orExp = orExp;
    }

    For(ForStmt *stmt1, Stmt *stmt) {
        this->stmt = stmt;
        this->forStmt1 = stmt1;
    }

    For(Stmt *stmt, ForStmt *stmt2) {//stmt2放末尾
        this->stmt = stmt;
        this->forStmt2 = stmt2;
    }
};


#endif //MID_CODE_FOR_H
