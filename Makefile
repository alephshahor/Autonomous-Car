CC = gcc
CXX = g++
RM = rm -f
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -o


AutonomousCar: cell.o field.o sensor.o car.o main.o
					$(CXX) cell.o field.o sensor.o car.o main.o $(FLAGS) AutonomousCar

cell.o: cell.cpp cell.hpp

field.o: field.cpp field.hpp

sensor.o: sensor.hpp sensor.cpp

car.o: car.hpp car.cpp

main.o: main.cpp

clean:
	$(RM) AutonomousCar cell.o field.o car.o sensor.o main.o
