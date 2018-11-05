#pragma once
#include <iostream>

enum CellObjects {Empty, Obstacle, Goal, Optimal};
enum Cardinality {North, South , East, West};
extern std::pair<int,int> fieldDimension;
extern int cellSize;
extern int initialPosX, finalPosX, initialPosY, finalPosY;

void setFieldDimension(int x, int y);
std::pair<int,int> getFieldDimension();
void setCellSize(int cellSize_);
int getCellSize();
