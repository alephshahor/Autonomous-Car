#include "goal.hpp"


Goal::Goal(std::pair<int,int> dimension, std::pair<int,int> position):
        dimension(dimension),
        position(position)
        {
          goalTexture.loadFromFile("./art/goal.png");
          goalDrawable.setSize(sf::Vector2f(dimension.first, dimension.second));
          goalDrawable.setPosition(position.first * dimension.first, position.second * dimension.second);
          goalDrawable.setTexture(&goalTexture);
        }

void Goal::draw(sf::RenderTarget& target, sf::RenderStates states) const{
         target.draw(goalDrawable);
}
