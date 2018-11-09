#pragma once
#include <iostream>

enum CellObjects {Empty, Obstacle, Goal, Optimal, Visited};
enum Cardinality {North, South , East, West};
extern std::pair<int,int> gFieldDimension;
extern int gCellSize;

void setFieldDimension(int x, int y);
std::pair<int,int> getFieldDimension();
void setCellSize(int cellSize_);
int getCellSize();
