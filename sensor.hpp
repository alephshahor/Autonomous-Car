#pragma once
#include <iostream>
#include "common.hpp"
#include "field.hpp"

class Sensor{

    private:

      Cardinality cardinality;
      bool isEmpty;

      public:


      Sensor(Cardinality cardinality);
      bool collisionCheck(Field simulationField, std::pair<int,int> carPosition);


};
