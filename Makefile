#Compiler
CC=g++
#Source files directory
SDIR=./src/
#Include files directory
IDIR=./include/
#Object files directory
ODIR=./obj/

SRC_FILES =			\
	Debugger.cpp	\
	Func.cpp		\
	Invar.cpp		\
	NFAs.cpp		\
	Parse.cpp		\
	Scanner.cpp		\
	Scope.cpp		\

OBJ_FILES = $(SRC_FILES:.cpp=.o)

Debugger : $(OBJ_FILES)
			$(CC) -std=c++17 -o Debugger $(OBJ_FILES)
			mkdir $(ODIR)
			mv $(OBJ_FILES) $(ODIR)

Debugger.o : $(SDIR)Debugger.cpp $(IDIR)Globals.h $(IDIR)Scanner.h $(IDIR)Parse.h
			$(CC) -std=c++17 -c $(SDIR)Debugger.cpp

Func.o : $(SDIR)Func.cpp $(IDIR)Func.h
			$(CC) -std=c++17 -c $(SDIR)Func.cpp

Invar.o : $(SDIR)Invar.cpp $(IDIR)Invar.h $(IDIR)Globals.h
			$(CC) -std=c++17 -c $(SDIR)Invar.cpp

NFAs.o : $(SDIR)NFAs.cpp $(IDIR)NFAs.h
			$(CC) -std=c++17 -c $(SDIR)NFAs.cpp

Parse.o : $(SDIR)Parse.cpp $(IDIR)Invar.h $(IDIR)Globals.h $(IDIR)Parse.h
			$(CC) -std=c++17 -c $(SDIR)Parse.cpp

Scanner.o : $(SDIR)Scanner.cpp $(IDIR)Scanner.h $(IDIR)Globals.h
			$(CC) -std=c++17 -c $(SDIR)Scanner.cpp

Scope.o : $(SDIR)Scope.cpp $(IDIR)Scope.h
			$(CC) -std=c++17 -c $(SDIR)Scope.cpp

.PHONY : clean

clean : FORCE
			rm -rf ./obj
FORCE :
