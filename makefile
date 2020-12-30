c=g++
all:
	$(c) -std=c++11 -w -c cpu.cpp -o cpu.o
	$(c) -std=c++11 -w -c main.cpp -o main.o
	$(c) -std=c++11 -w main.o cpu.o -o main