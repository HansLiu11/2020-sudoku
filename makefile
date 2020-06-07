all: transform generate solve

transform: transform.o sudoku.o
	g++ -O2 -o transform transform.o sudoku.o

generate: generate.o sudoku.o
	g++ -O2 -o generate generate.o sudoku.o

solve: solve.o sudoku.o
	g++ -O2 -o solve solve.o sudoku.o

transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean:
	rm transform *.o

