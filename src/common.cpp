#include "common.hpp"

std::pair<int,int> fieldDimension = std::make_pair(1,1);
int cellSize = 0;


int initialPosX = 0;
int finalPosX = 0;
int initialPosY = 0;
int finalPosY = 0;

void setFieldDimension(int x, int y){
    fieldDimension = std::make_pair(x,y);
}

std::pair<int,int> getFieldDimension(){
    return fieldDimension;
}

void setCellSize(int cellSize_){
  cellSize = cellSize_;
}

int getCellSize(){
  return cellSize;
}
