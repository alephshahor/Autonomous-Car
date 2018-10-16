#pragma once
#include <iostream>
#include "cell.hpp"


// Consider the field border as non available space to access.

class Field{

  private:

      float cellSize;
      std::vector< std::vector<Cell> > vectorOfCells;
      std::pair<int,int> fieldDimension;


    public:

        // Constructors
        Field(int width, int height, float cellSize);
        Field(std::pair<int,int> fieldDimension, float cellSize);

        // Getters
        Cell getCell(int posX, int posY);
        int getWidth();
        int getHeight();

        //  This function changes the cell from dead to alive and vice versa
        void changeCellState(int posX, int posY);



};
