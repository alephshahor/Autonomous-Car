#include "car.hpp"

Car::Car(std::pair<int,int> dimension, std::pair<int,int> position):
        vSensors(),
        dimension(dimension),
        position(position)
        {

          carTexture.loadFromFile("./art/redTexture_.jpeg");
          carDrawable.setSize(sf::Vector2f(dimension.first, dimension.second));
          carDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
          carDrawable.setTexture(&carTexture);
        }

void Car::moveRight(){
    position.first += 1;
}

void Car::moveLeft(){
    position.first -= 1;
}

void Car::moveUp(){
    position.second += 1;
}

void Car::moveDown(){
    position.second -= 1;
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     target.draw(carDrawable);
}

std::pair<int,int> Car::getPosition(){
      return position;
}
