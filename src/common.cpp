#include "common.hpp"

std::pair<int,int> fieldDimension = std::make_pair(1,1);

void setFieldDimension(int x, int y){
    fieldDimension = std::make_pair(x,y);
}
