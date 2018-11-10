#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sensor.hpp"
#include "field.hpp"
#include "common.hpp"

class autonomousCar : public sf::Drawable {


    private:

      std::vector <Sensor> vSensors;
      std::pair <int,int> dimension; // (x,y)
      std::pair <int,int> position;
      sf::Texture carTexture;
      sf::RectangleShape carDrawable;

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

      public:

        autonomousCar(std::pair<int,int> dimension, std::pair<int,int> position);
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        bool checkUpwardsCollision(Field simulationField);
        bool checkBackwardsCollision(Field simulationField);
        bool checkRightCollision(Field simulationField);
        bool checkLeftCollision(Field simulationField);

        std::pair<int,int> getPosition();
        void setPosition(std::pair<int,int> position);



};
