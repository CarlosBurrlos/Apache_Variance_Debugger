cmake_minimum_required(VERSION 3.10)
project(beta)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Prototyping)

add_executable(beta
        Prototyping/main.cpp
        Prototyping/Scnr_P.cpp
        Prototyping/Scnr_P.h)
