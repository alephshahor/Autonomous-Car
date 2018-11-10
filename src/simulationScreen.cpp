#include "simulationScreen.hpp"

void simulationScreen::display(sf::RenderWindow& window, Field simulationField, autonomousCar ferrari){

  std::pair<int,int> carPos = ferrari.getPosition();
  window.clear();
  for (int i = 0; i < simulationField.getWidth(); i++){
    for (int j = 0; j < simulationField.getHeight(); j++){
      if ((i == carPos.first) && (j == carPos.second))
           window.draw(ferrari);
      else window.draw(simulationField.getCell(i,j));
      }
    }


  window.display();
}


int simulationScreen::Run(sf::RenderWindow& window){

std::cout << "Field dimension is " << gFieldDimension.first << " , " << gFieldDimension.second << "\n";
Field simulationField(gFieldDimension.first,gFieldDimension.second,float(getCellSize()));
//Field simulationField(20,20,1);


std::cout << "I made it\n";
std::pair<int,int> carDimension = std::make_pair(getCellSize(),getCellSize());
std::pair<int,int> carPosition = std::make_pair(10,10);
std::pair<int,int> finalPos = std::make_pair(3,3);
autonomousCar ferrari(carDimension, carPosition);
CellObjects currentCellObject = Obstacle;

bool running = true;
bool pause = false;
bool optimalRoute = false;
bool sequentialMode = false;


display(window, simulationField, ferrari);

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
                 simulationField.changeCellState(evnt.mouseButton.x, evnt.mouseButton.y, currentCellObject);
             if (currentCellObject == Goal)
                 finalPos = std::make_pair(evnt.mouseButton.x / gCellSize , evnt.mouseButton.y / gCellSize);
             display(window, simulationField, ferrari);
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
             if (evnt.key.code == sf::Keyboard::Num8){
                  if (!sequentialMode){
                    sequentialMode = true;
                    std::cout << "SEQUENTIAL MODE : ON\n";
                  }else{
                    sequentialMode = false;
                    std::cout << "SEQUENTIAL MODE : OFF\n";
                  }
              }

              if (evnt.key.code == sf::Keyboard::Num2){
                  currentCellObject = Obstacle;
                  std::cout << "SELECTED OBJECT: OBSTACLE\n";
                }

              if (evnt.key.code == sf::Keyboard::Num3){
                  currentCellObject = Goal;
                  std::cout << "SELECTED OBJECT: GOAL\n";
                }

             if ((evnt.key.code == sf::Keyboard::Num1) && (!optimalRoute)){

                  optimalRoute = true;
                  std::pair<int,int> carPos = ferrari.getPosition();
                  std::list<Node> cellRoute = simulationField.calculateOptimalRoute(carPos, finalPos);

                  Node* finalNode;

                  if (!sequentialMode){
                  for (auto node: cellRoute){
                    simulationField.changeCellState(node.getPosition().first * gCellSize , node.getPosition().second * gCellSize, Visited);
                    if (node.getPosition().first == finalPos.first && node.getPosition().second == finalPos.second)
                        finalNode = &node;
                      }

                  while (finalNode != NULL){
                      simulationField.changeCellState(finalNode -> getPosition().first * gCellSize , finalNode -> getPosition().second * gCellSize, Optimal);
                      finalNode = finalNode -> getParent();
                  }

                }else{
                  for (auto node: cellRoute){
                    if (node.getPosition().first == finalPos.first && node.getPosition().second == finalPos.second)
                        finalNode = &node;
                    else simulationField.changeCellState(node.getPosition().first * gCellSize , node.getPosition().second * gCellSize, Visited);
                    display(window, simulationField, ferrari);
                      }

                  while (finalNode -> getParent() != NULL){
                      finalNode = finalNode -> getParent();
                      simulationField.changeCellState(finalNode -> getPosition().first * gCellSize , finalNode -> getPosition().second * gCellSize, Optimal);
                      display(window, simulationField, ferrari);

                }
             }

           }

             if (evnt.key.code == sf::Keyboard::Num9){
                 optimalRoute = false;
                 simulationField.reset();
                 ferrari.setPosition(carPosition);
             }


             display(window, simulationField, ferrari);


             break;

    }

  }

  }

  // End of the simulation
  return -1;

}
