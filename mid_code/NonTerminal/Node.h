//
// Created by 86152 on 15/11/2023.
//
#include "../IntTable.h"
#include "../FuncTable.h"
#include <vector>
#include "fstream"
#include <stack>
#include "../Reg.h"

using namespace std;

#ifndef ERROR_NODE_H
#define ERROR_NODE_H

extern ofstream fout;

class Node {
public:
    static IntTable *intTable;
    static FuncTable *funcTable;
    static int labels;
    static stack<int> myStack;

//    Node() {
//        myStack = stack<int>();
//    }

    virtual void out() {

    }

    virtual string genIR() {
        return "";
    }

    static void irPrint(string t1, string op, string t2, string t3) {

        fout << t1 << " = ";
        if (op == "+") {
            fout << "add";
        } else if (op == "-") {
            fout << "sub";
        } else if (op == "*") {
            fout << "mul";
        } else if (op == "/") {
            fout << "sdiv";
        } else if (op == "%") {
            fout << "srem";
        }

        fout << " i32 " << t2 << ", " << t3 << endl;
    }

    static void retPrint(string reg) {
        fout << "ret i32 " << reg << endl;
    }

    static void outDefPrint(string name, bool isConst, int value) {
        if (isConst)
            fout << "@" << name << " = dso_local constant i32 " << value << endl;
        else
            fout << "@" << name << " = dso_local global i32 " << value << endl;

    }

    static void myalloca(string reg) {
        //%1 = alloca i32
        fout << reg << " = alloca i32" << endl;
    }

    static void myalloca(string reg, int n) {
        //%4 = alloca [3 x i32]
        fout << reg << " = alloca [" << n << " x i32]" << endl;
    }

    static void myalloca1(string reg) {
        //%1 = alloca i32
        fout << reg << " = alloca i32*" << endl;
    }

    static void mystore(string reg1, string reg2) {
        //store i32 %2, i32* %1
        fout << "store i32 " << reg1 << ", i32* " << reg2 << endl;
    }

    static void mystore1(string reg1, string reg2) {
        //store i32 %2, i32* %1
        fout << "store i32 " << reg1 << ", i32* * " << reg2 << endl;
    }

    static void myload(string reg1, string outVar) {
        // %2 = load i32, i32* @c
        fout << reg1 << " = load i32, i32* " << outVar << endl;
    }

    static void myload1(string reg1, string outVar) {
        // %2 = load i32, i32* @c
        fout << reg1 << " = load i32*, i32* * " << outVar << endl;
    }
//    static void myloadarr(string reg1, string outVar) {
//        //%11 = getelementptr [6 x i32], [6 x i32]* @a, i32 0, i32 4
//        fout << reg1 << " = load i32, i32* " << outVar << endl;
//    }

    static void mygetint(string reg1) {
        //%3 = call i32 @getint()
        fout << reg1 << " = call i32 @getint()" << endl;
    }

    static void myputch(int ch) {
        //call void @putch(i32 58)
        fout << "call void @putch(i32 " << ch << ")" << endl;
    }

    static void myputint(string reg) {
        //call void @putint(i32 %4)
        fout << "call void @putint(i32 " << reg << ")" << endl;
    }

    static void myparams(vector<string> *str) {
        if (str->size() > 0) {
            fout << "i32 " << (*str)[0];
        }

        for (int i = 1; i < str->size(); ++i) {
            fout << ", i32 " << (*str)[i];
        }
    }

    static void myfuncr(string reg, string funcr) {
        //call i32 @aaa(i32 %5, i32 %6)
        fout << reg << " = " << funcr << endl;
    }

    static void myfuncr(string funcr) {
        //call i32 @aaa(i32 %5, i32 %6)
        fout << funcr << endl;
    }

    static void mylabel(string label) {
        //call i32 @aaa(i32 %5, i32 %6)
        fout << label << ":" << endl;
    }

    static void mycmp(string t1, string op, string t2, string t3) {
        //%result = icmp slt i32 %a, %b
        fout << t1 << " = icmp ";
        if (op == "==") {
            fout << "eq";
        } else if (op == "!=") {
            fout << "ne";
        } else if (op == "<") {
            fout << "slt";
        } else if (op == ">") {
            fout << "sgt";
        } else if (op == "<=") {
            fout << "sle";
        } else if (op == ">=") {
            fout << "sge";
        }
        fout << " i32 " << t2 << ", " << t3 << endl;
    }

    static void mybr(string label) {
        //br label %12
        fout << "br label " << label << endl;
    }

    static void mybr(string reg, string label1, string label2) {
        //br i1 %8, label %12, label %9
        fout << "br i1 " << reg << ", label " <<
             label1 << ", label " << label2 << endl;
    }

    static void mytranc(string reg1, string reg2) {
        //%truncated_val_i16 = trunc i32 %val_i32 to i16
        fout << reg1 << " = trunc i32 " << reg2 << " to i16" << endl;
    }

    static void outarr(string name, bool isConst, int num, vector<int> values) {
//  @a = dso_local global [6 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 6]
        if (isConst) {
            fout << "@" << name << " = dso_local constant ["
                 << num << " x i32] [i32 " << values[0];
            for (int i = 1; i < values.size(); ++i) {
                fout << ", i32 " << values[i];
            }
            fout << "]" << endl;
        } else {
            fout << "@" << name << " = dso_local global ["
                 << num << " x i32] [i32 " << values[0];
            for (int i = 1; i < values.size(); ++i) {
                fout << ", i32 " << values[i];
            }
            fout << "]" << endl;
        }
    }

    static void outarr(string name, bool isConst, int num) {
        //@b = dso_local global [10 x [20 x i32]] zeroinitializer
        if (isConst) {
            fout << "@" << name << " = dso_local constant ["
                 << num << " x i32] zeroinitializer" << endl;
        } else {
            fout << "@" << name << " = dso_local global ["
                 << num << " x i32] zeroinitializer" << endl;
        }
    }

    static void getelementptr(string reg1, string reg2, string k, int n) {//n数组总大小，k查找第几个
        //%6 = getelementptr i32, i32* %5, i32 4
        //%a9_as_i32_ptr = bitcast [6 x i32]* %a9 to i32*
        //%5 = getelementptr [7 x i32], [7 x i32]* %4, i32 3, i32 0

//        Reg *reg = new Reg();
//        fout << reg->toString() << " = bitcast [" << n << " x i32]* " << reg2 << " to i32*" << endl;
//        fout << reg1 << " = getelementptr i32, i32* " << reg->toString() << ", i32 " << k << endl;
        fout << reg1 << " = getelementptr [" << n << " x i32], [" << n << " x i32]* " << reg2 << ", i32 0, i32 " << k
             << endl;
    }

    static void getelementptr(string reg1, string reg2, int k, int n) {//n数组总大小，k查找第几个
        fout << reg1 << " = getelementptr [" << n << " x i32], [" << n << " x i32]* " << reg2 << ", i32 0, i32 " << k
             << endl;
    }

    static void getelementptr(string reg1, string reg2, string k) {//n数组总大小，k查找第几个
        fout << reg1 << " = getelementptr i32, i32* " << reg2 << ",i32 " << k << endl;
    }

    static void myZext(string reg1, string reg2, int pre, int now) {
        //%value_i32 = zext i8 %value_i8 to i32
        fout << reg1 << " = zext i" << pre << " " << reg2 << " to i" << now << endl;
    }
};

#endif //ERROR_NODE_H
