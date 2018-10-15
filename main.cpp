#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"


int main(){


sf::RenderWindow window(sf::VideoMode(480,480), "Autonomous Car", sf::Style::Close);
Field simulationField(480,480,10.0f);

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

  window.clear();
  for (int i = 0; i < simulationField.getHeight(); i++){
    for (int j = 0; j < simulationField.getWidth(); j++){
      window.draw(simulationField.getCell(i,j));
    }
  }

  window.display();



  }

}
