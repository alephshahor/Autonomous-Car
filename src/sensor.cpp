#include "sensor.hpp"

Sensor::Sensor(Cardinality cardinality):
        cardinality(cardinality)
        {}

bool Sensor::collisionCheck(Field simulationField, std::pair<int,int> carPosition){

    switch(cardinality){

      case 0:
      return simulationField.getCell(carPosition.first, carPosition.second - 1).isOccupied();

      break;

      case 1:
      return simulationField.getCell(carPosition.first, carPosition.second + 1).isOccupied();
      break;

      case 2:
      return simulationField.getCell(carPosition.first + 1, carPosition.second).isOccupied();
      break;

      case 3:
      return simulationField.getCell(carPosition.first - 1, carPosition.second).isOccupied();
      break;

      default:
      break;
    }

}
