CC = gcc
CXX = g++
RM = rm -f
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -o


AutonomousCar: cell.o field.o car.o sensor.o main.o
					$(CXX) cell.o field.o car.o sensor.o main.o $(FLAGS) AutonomousCar

cell.o: cell.cpp cell.hpp

field.o: field.cpp field.hpp

car.o: car.hpp car.cpp

sensor.o: sensor.hpp sensor.cpp

main.o: main.cpp

clean:
	$(RM) AutonomousCar cell.o field.o car.o sensor.o main.o
