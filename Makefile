
TARGET = AutonomousCar

SRC = src
INC = include
BIN = bin
FLAGS =  -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -std=c++11 -I$(INC)

SOURCE = $(wildcard $(SRC)/*.cpp)
OBJECT = $(patsubst %, $(BIN)/% ,$(notdir $(SOURCE:.cpp=.o)))

CXX = g++

$(BIN)/$(TARGET) : $(OBJECT)
				$(CXX) -o $@ $^ $(FLAGS)

# -c "Compile but not link"
$(BIN)/%.o : $(SRC)/%.cpp
				$(CXX) $(CFLAGS) -c -gstabs $< -o $@

.PHONY: help run clean

run : $(BIN)/$(TARGET)
				$(BIN)/$(TARGET)

clean:
		rm -f $(OBJECT) $(BIN)/$(TARGET)


help:
		@echo "src: $(SOURCE)"
		@echo "obj: $(OBJECT)"
