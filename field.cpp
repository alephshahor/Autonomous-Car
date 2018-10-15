#include "field.hpp"

Field::Field(int width, int height, float cellSize):
       cellSize(cellSize),
       vectorOfCells(),
       fieldDimension(std::make_pair(width,height))
       {

         for (int i = 0; i < height / cellSize; i++){
             std::vector<Cell> vCells;
             for (int j = 0; j < width / cellSize; j++){
               vCells.push_back(Cell(cellSize,10.0f*j, 10.0f*i));
             }
               vectorOfCells.push_back(vCells);
         }

         for (int i = 0; i < height / cellSize; i++){
             for (int j = 0; j < width / cellSize; j++){
               vectorOfCells[i][j].setTexture(Empty);
             }
         }

       }

Field::Field(std::pair<int,int> fieldDimension, float cellSize):
        cellSize(cellSize),
        vectorOfCells(),
        fieldDimension(fieldDimension)
        {

          for (int i = 0; i < fieldDimension.second / cellSize; i++){
              std::vector<Cell> vCells;
              for (int j = 0; j < fieldDimension.first / cellSize; j++){
                vCells.push_back(Cell(cellSize,10.0f*j, 10.0f*i));
              }
                vectorOfCells.push_back(vCells);
          }

          /* This is necessary because when you use push_back you're actually
          creating a copy of the object you're inserting so you lose the
          texture reference*/
          for (int i = 0; i < fieldDimension.second / cellSize; i++){
              for (int j = 0; j < fieldDimension.first / cellSize; j++){
                vectorOfCells[i][j].setTexture(Empty);
              }
          }


        }

Cell Field::getCell(int posX, int posY){
        return vectorOfCells[posY][posX];
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

    vectorOfCells[posY][posX].setTexture(cellObject);
}
