#include "common.hpp"

std::pair<int,int> gFieldDimension = std::make_pair(1,1);
int gCellSize = 0;
Heuristic gHeuristic = Euclidean;


void setFieldDimension(int x, int y){
    gFieldDimension = std::make_pair(x,y);
}

std::pair<int,int> getFieldDimension(){
    return gFieldDimension;
}

void setCellSize(int cellSize_){
  gCellSize = cellSize_;
}

int getCellSize(){
  return gCellSize;
}
