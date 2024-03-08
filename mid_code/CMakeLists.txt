cmake_minimum_required(VERSION 3.15)
project(mid_code)

set(CMAKE_CXX_STANDARD 17)

add_executable(lexer Lexer.cpp Lexer.h  main.cpp main.h Token.cpp Token.h NonTerminal/IntIdent.h NonTerminal.h PreParser.cpp PreParser.h IntTable.h FuncTable.h NonTerminal/FuncIdent.h StrToken.h NonTerminal/Root.h NonTerminal/Node.h NonTerminal/Decl.h NonTerminal/Func.h NonTerminal/BlockItem.h NonTerminal/Def.h NonTerminal/AndExp.h NonTerminal/Stmt.h NonTerminal/Block.h NonTerminal/FParam.h NonTerminal/Exp.h NonTerminal/OrExp.h NonTerminal/LVal.h NonTerminal/Var.h NonTerminal/Array.h NonTerminal/ConstDef.h NonTerminal/VarDef.h NonTerminal/If.h NonTerminal/For.h NonTerminal/ForStmt.h NonTerminal/Break.h NonTerminal/Continue.h NonTerminal/MyReturn.h NonTerminal/MyPrintf.h NonTerminal/Getint.h NonTerminal/Assign.h NonTerminal/FuncR.h NonTerminal/UnaryExp.h NonTerminal/CalExp.h NonTerminal/LogExp.h NonTerminal/Number.h Parser.cpp Parser.h Reg.h Reg.cpp NonTerminal/Node.cpp Label.cpp Label.h NonTerminal/Block.cpp NonTerminal/AndExp.cpp NonTerminal/OrExp.cpp NonTerminal/ArrayIdent.h)

set(CMAKE_CXX_FLAGS "-g")