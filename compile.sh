bison -o parser.cpp -d -t src/parser.y
flex -o lexer.cpp -d src/lexer.l
g++ -c -o lexer.o lexer.cpp
g++ -c -o parser.o parser.cpp
g++ -c -o visitor.o src/visitor.cpp
g++ main.cpp parser.o lexer.o visitor.o