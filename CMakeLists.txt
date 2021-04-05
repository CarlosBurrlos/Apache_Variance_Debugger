cmake_minimum_required(VERSION 3.17)
project(408Debugger)

set(CMAKE_CXX_STANDARD 17)

add_executable(408Debugger Debugger/Debug.cpp Debugger/Scanner.cpp Debugger/Scope.cpp Debugger/Parser.cpp Headers/Debugger.h Debugger/NFAs.cpp Headers/NFAs.h Headers/Scanner.h Headers/Scope.h Headers/Parser.h Headers/Func.h Headers/All.h Headers/Globals.h Debugger/Func.cpp Headers/Invar.h Debugger/Invar.cpp)