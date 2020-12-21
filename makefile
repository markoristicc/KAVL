CXX = clang++

CXXFLAGS = -std=c++11 -Wall 

BINARIES = project3.out

all: ${BINARIES}

project3.out: main.o KAVL.o knode.o
	${CXX} $^ -o $@

clean: 
	/bin/rm -f ${BINARIES} *.o
