//
// Created by 86152 on 21/11/2023.
//

#include "Node.h"

IntTable* Node::intTable = new IntTable();
FuncTable* Node::funcTable = new FuncTable();
int Node::labels = 0;
stack<int> Node::myStack = stack<int>();