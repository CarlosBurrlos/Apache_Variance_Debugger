goal: scope scanner parser func

scope:
	g++ -g -std=c++17 -Wall -Wextra -pedantic -o Scope.cpp

scanner:
	g++ -g -std=c++17 -Wall -Wextra -pedantic -o Scanner.cpp

parser:
	g++ -g -std=c++17 -Wall -Wextra -pedantic -o Parser.cpp

func:
	g++ -g -std=c++17 -Wall -Wextra -pedantic -o Func.cpp

clean:
  rm -rf *.o