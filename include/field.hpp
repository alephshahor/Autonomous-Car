#pragma once
#include <iostream>
#include <cmath>
#include <deque>
#include "cell.hpp"
#include "node.hpp"


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
        std::vector<Node> calculateChilds(Node* targetNode);
        int calculateHeuristic(Node targetNode, std::pair<int,int> finalPos);
        int calculateFunction(Node targetNode, std::pair<int,int> finalPos, int actualWeight);
        void calculateOptimalRoute(std::pair<int,int> initialPos, std::pair<int,int> finalPos);







};
