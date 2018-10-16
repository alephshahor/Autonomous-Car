#include "car.hpp"

autonomousCar::autonomousCar(std::pair<int,int> dimension, std::pair<int,int> position):
        vSensors(),
        dimension(dimension),
        position(position)
        {
          carTexture.loadFromFile("./art/redTexture_.jpeg");
          carDrawable.setSize(sf::Vector2f(dimension.first, dimension.second));
          carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
          carDrawable.setTexture(&carTexture);

          vSensors.push_back(Sensor(North));
          vSensors.push_back(Sensor(South));
          vSensors.push_back(Sensor(East));
          vSensors.push_back(Sensor(West));

        }

bool autonomousCar::checkUpwardsCollision(Field simulationField){
    return vSensors[North].collisionCheck(simulationField, position);
  }

bool autonomousCar::checkBackwardsCollision(Field simulationField){
    return vSensors[South].collisionCheck(simulationField, position);
  }

bool autonomousCar::checkRightCollision(Field simulationField){
    return vSensors[East].collisionCheck(simulationField, position);
  }

bool autonomousCar::checkLeftCollision(Field simulationField){
   return vSensors[West].collisionCheck(simulationField, position);
  }

void autonomousCar::moveRight(){
    position.first += 1;
    carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
}

void autonomousCar::moveLeft(){
    position.first -= 1;
    carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
}

void autonomousCar::moveUp(){
    position.second -= 1;
    carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
}

void autonomousCar::moveDown(){
    position.second += 1;
    carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
}

void autonomousCar::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     target.draw(carDrawable);
}

std::pair<int,int> autonomousCar::getPosition(){
      return position;
}
