#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"

int main(){


sf::RenderWindow window(sf::VideoMode(500,500), "Autonomous Car", sf::Style::Close);
Field simulationField(500,400,20.0f);
std::pair<int,int> carDimension = std::make_pair(20,20);
std::pair<int,int> carPosition = std::make_pair(10,10);
autonomousCar ferrari(carDimension, carPosition);

bool running = true;

while (running){
  sf::Event evnt;
  while(window.pollEvent(evnt)){

    switch(evnt.type){
      case sf::Event::Closed:
           window.close();
           return -1;
           break;
      case sf::Event::MouseButtonPressed:
             if (evnt.mouseButton.button == sf::Mouse::Left)
             simulationField.changeCellState(evnt.mouseButton.x, evnt.mouseButton.y);
             break;
      case sf::Event::KeyPressed:
             std::cout << evnt.key.code << "\n";
             if (evnt.key.code == sf::Keyboard::Escape)
               running = false;
             if (evnt.key.code == sf::Keyboard::D && !ferrari.checkRightCollision(simulationField))
               ferrari.moveRight();
             if (evnt.key.code == sf::Keyboard::A && !ferrari.checkLeftCollision(simulationField))
               ferrari.moveLeft();
             if (evnt.key.code == sf::Keyboard::W && !ferrari.checkUpwardsCollision(simulationField))
               ferrari.moveUp();
             if (evnt.key.code == sf::Keyboard::S && !ferrari.checkBackwardsCollision(simulationField))
               ferrari.moveDown();

             break;
    }

  }

  std::pair<int,int> carPos = ferrari.getPosition();
  window.clear();
  for (int i = 0; i < simulationField.getWidth(); i++){
    for (int j = 0; j < simulationField.getHeight(); j++){
      window.draw(simulationField.getCell(i,j));
      if ((i == carPos.first) && (j == carPos.second))
           window.draw(ferrari);
    }
  }

  window.display();



  }

}
