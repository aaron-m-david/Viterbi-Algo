#Aaron David
#Makefile

a.out: main.cpp
	g++ -g -Wall -std=c++11 main.cpp
clean:
	rm a.out