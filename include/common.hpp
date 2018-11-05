#pragma once
#include <iostream>

enum CellObjects {Empty, Obstacle, Goal, Optimal};
enum Cardinality {North, South , East, West};
extern std::pair<int,int> fieldDimension;

void setFieldDimension(int x, int y);
