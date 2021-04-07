#Compiler
CC=g++
#Source files directory
SDIR=./src/
#Include files directory
IDIR=./include/

Debugger : Debugger.o Func.o Invar.o NFAs.o Parser.o Scanner.o Scope.o
			$(CC) -std=c++17 -o Debugger Debugger.o Func.o Invar.o NFAs.o Parser.o Scanner.o Scope.o

Debugger.o : $(SDIR)Debugger.cpp $(IDIR)Globals.h $(IDIR)Scanner.h $(IDIR)Parser.h
			$(CC) -std=c++17 -c $(SDIR)Debugger.cpp

Func.o : $(SDIR)Func.cpp $(IDIR)Func.h
			$(CC) -std=c++17 -c $(SDIR)Func.cpp

Invar.o : $(SDIR)Invar.cpp $(IDIR)Invar.h $(IDIR)Globals.h
			$(CC) -std=c++17 -c $(SDIR)Invar.cpp

NFAs.o : $(SDIR)NFAs.cpp $(IDIR)NFAs.h
			$(CC) -std=c++17 -c $(SDIR)NFAs.cpp

Parser.o : $(SDIR)Parser.cpp $(IDIR)Invar.h $(IDIR)Globals.h $(IDIR)Parser.h
			$(CC) -std=c++17 -c $(SDIR)Parser.cpp

Scanner.o : $(SDIR)Scanner.cpp $(IDIR)Scanner.h $(IDIR)Globals.h
			$(CC) -std=c++17 -c $(SDIR)Scanner.cpp

Scope.o : $(SDIR)Scope.cpp $(IDIR)Scope.h
			$(CC) -std=c++17 -c $(SDIR)Scope.cpp

.PHONY : clean

clean : FORCE
			rm -f *.o
FORCE :
