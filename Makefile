CC = gcc
CXX = g++
RM = rm -f
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -o


AutonomousCar: cell.o field.o main.o
					$(CXX) cell.o field.o main.o $(FLAGS) AutonomousCar

cell.o: cell.cpp cell.hpp

field.o: field.cpp field.hpp

main.o: main.cpp

clean:
	$(RM) AutonomousCar cell.o field.o main.o
