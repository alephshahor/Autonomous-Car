#pragma once
#include <iostream>

enum cellObjects {Empty, Obstacle, Goal};
enum Cardinality {North, South , East, West};
extern std::pair<int,int> fieldDimension;

void setFieldDimension(int x, int y);
