#include "field.hpp"

Field::Field(int width, int height, float cellSize):
       cellSize(cellSize),
       vectorOfCells(),
       fieldDimension(std::make_pair(width,height))
       {

         for (int i = 0; i < width / cellSize; i++){
             std::vector<Cell> vCells;
             for (int j = 0; j < height / cellSize; j++){
               vCells.push_back(Cell(cellSize, cellSize*i, cellSize*j));
             }
               vectorOfCells.push_back(vCells);
         }

         for (int i = 0; i < width / cellSize; i++){
             for (int j = 0; j < height / cellSize; j++){
               vectorOfCells[i][j].setTexture(Empty);
             }
         }

       }

Field::Field(std::pair<int,int> fieldDimension, float cellSize):
        cellSize(cellSize),
        vectorOfCells(),
        fieldDimension(fieldDimension)
        {

          for (int i = 0; i < fieldDimension.first / cellSize; i++){
              std::vector<Cell> vCells;
              for (int j = 0; j < fieldDimension.second / cellSize; j++){
                vCells.push_back(Cell(cellSize, cellSize*i, cellSize*j));
              }
                vectorOfCells.push_back(vCells);
          }

          /* This is necessary because when you use push_back you're actually
          creating a copy of the object you're inserting so you lose the
          texture reference*/
          for (int i = 0; i < fieldDimension.first / cellSize; i++){
              for (int j = 0; j < fieldDimension.second / cellSize; j++){
                vectorOfCells[i][j].setTexture(Empty);
              }
          }


        }

Cell Field::getCell(int posX, int posY){
        return vectorOfCells[posX][posY];
}

int Field::getWidth(){
  return fieldDimension.first / cellSize;
}

int Field::getHeight(){
  return fieldDimension.second / cellSize;
}

void Field::changeCellState(int posX, int posY, cellObjects cellObject){

    posX /= cellSize;
    posY /= cellSize;

    vectorOfCells[posX][posY].setTexture(cellObject);
}
