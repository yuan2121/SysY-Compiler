//
// Created by 86152 on 13/10/2023.
//

#include <string>
#include <vector>


using namespace std;

#ifndef ERROR_FUNCIDENT_H
#define ERROR_FUNCIDENT_H

class FuncIdent {
private:
    int line = 0;
    string name;
    vector<IntIdent> *params = new vector<IntIdent>();
    string type;

    vector<int> *params_ir = new vector<int>();
public:
    FuncIdent(string name1, int line1, vector<IntIdent> params1, string type1) {
        line = line1;
        name = name1;
        *params = params1;
        type = type1;
    }

    FuncIdent(string name1, vector<int> *params_ir1) {
        name = name1;
        params_ir = params_ir1;
    }

    FuncIdent() {

    }

    FuncIdent(string name1, string type1, vector<int> *params_ir1) {
        name = name1;
        type = type1;
        params_ir = params_ir1;
    }

    string getName() {
        return name;
    }

    int getPara(int i) {
        return (*params_ir)[i];
    }

    int getLine() {
        return line;
    }

    vector<IntIdent> getParams() {
        return *params;
    }

    string getType() {
        return type;
    }

};

#endif //ERROR_FUNCIDENT_H
