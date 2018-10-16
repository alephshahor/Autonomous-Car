#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"

int main(){


sf::RenderWindow window(sf::VideoMode(480,480), "Autonomous Car", sf::Style::Close);
Field simulationField(480,480,10.0f);
std::pair<int,int> carDimension = std::make_pair(10,10);
std::pair<int,int> carPosition = std::make_pair(10,10);
Car ferrari(carDimension, carPosition);

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
             simulationField.changeCellState(evnt.mouseButton.x, evnt.mouseButton.y, Obstacle);
             break;
    }

  }

  std::pair<int,int> carPos = ferrari.getPosition();
  window.clear();
  for (int i = 0; i < simulationField.getWidth(); i++){
    for (int j = 0; j < simulationField.getHeight(); j++){
      window.draw(simulationField.getCell(i,j));
      if ((i == carPos.first) && (j == carPos.second))
           ferrari.draw();
    }
  }

  window.display();



  }

}
