cmake_minimum_required(VERSION 3.17)
project(408Debugger)

set(CMAKE_CXX_STANDARD 17)

add_executable(408Debugger src/Debug.cpp src/Scanner.cpp src/Scope.cpp src/Parser.cpp include/Debugger.h src/NFAs.cpp include/NFAs.h include/Scanner.h include/Scope.h include/Parser.h include/Func.h include/All.h include/Globals.h src/Func.cpp include/Invar.h src/Invar.cpp)