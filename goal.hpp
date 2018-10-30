#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common.hpp"


class Goal{

  private:

    std::pair <int, int> dimension;
    std::pair <int, int> position;
    sf::Texture goalTexture;
    sf::RectangleShape goalDrawable;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:

      Goal(std::pair<int,int> dimension, std::pair<int,int> position);



};
