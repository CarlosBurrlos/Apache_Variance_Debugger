cmake_minimum_required(VERSION 3.17)
project(408Debugger)

set(CMAKE_CXX_STANDARD 14)

include_directories(pi/partA/include)

add_executable(408Debugger
        pi/partA/include/Func.h
        pi/partA/include/Globals.h
        pi/partA/include/Invar.h
        pi/partA/include/NFAs.h
        pi/partA/include/Parse.h
        pi/partA/include/Scanner.h
        pi/partA/include/Scope.h
        pi/partA/src/Debugger.cpp
        pi/partA/src/Func.cpp
        pi/partA/src/Invar.cpp
        pi/partA/src/NFAs.cpp
        pi/partA/src/Parse.cpp
        pi/partA/src/Scanner.cpp
        pi/partA/src/Scope.cpp)
