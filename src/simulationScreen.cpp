#include "simulationScreen.hpp"

int simulationScreen::Run(sf::RenderWindow& window){

std::cout << "Field dimension is " << gFieldDimension.first << " , " << gFieldDimension.second << "\n";
Field simulationField(gFieldDimension.first,gFieldDimension.second,float(getCellSize()));
//Field simulationField(20,20,1);


std::cout << "I made it\n";
std::pair<int,int> carDimension = std::make_pair(getCellSize(),getCellSize());
std::pair<int,int> carPosition = std::make_pair(10,10);
autonomousCar ferrari(carDimension, carPosition);

bool running = true;
bool pause = false;
bool optimalRoute = false;

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
             if ((evnt.key.code == sf::Keyboard::Num1) && (!optimalRoute)){

                  std::pair<int,int> carPos = ferrari.getPosition();
                  std::list<Node> cellRoute = simulationField.calculateOptimalRoute(carPos, std::make_pair(3,3));

                  for (auto node: cellRoute)
                    simulationField.changeCellState(node.getPosition().first * gCellSize , node.getPosition().second * gCellSize, Visited);
                    window.clear();

             }

             break;
    }

  }

  if (!pause){
  std::pair<int,int> carPos = ferrari.getPosition();
  window.clear();
  for (int i = 0; i < simulationField.getWidth(); i++){
    for (int j = 0; j < simulationField.getHeight(); j++){
      if ((i == carPos.first) && (j == carPos.second))
           window.draw(ferrari);
      else window.draw(simulationField.getCell(i,j));
      }
    }
  }

  window.display();



  }

  // End of the simulation
  return -1;

}
