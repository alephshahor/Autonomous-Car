#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <set>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"
#include "initialScreen.hpp"
#include "simulationScreen.hpp"
#include "testScreen.hpp"
#include "test.hpp"

struct lex_compare{
  bool operator() (const Node* targetNode1, const Node* targetNode2) const{
    return targetNode1 < targetNode2;
  }
};

Heuristic selectHeuristicFunction(){

  std::cout << "SELECT HEURISTIC FUNCTION:\n";
  std::cout << "[0] MANHATTAN\n";
  std::cout << "[1] EUCLIDEAN\n";
  int hFunction = -1;
  std::cin >> hFunction;

  Heuristic heuristicFunction;
  bool unselected = true;
  while (unselected){
    switch(hFunction){
        case 0:
        std::cout << "MANHATTAN FUNCTION SELECTED\n";
        unselected = false;
        heuristicFunction = Manhattan;
        break;
        case 1:
        std::cout << "EUCLIDEAN FUNCTION SELECTED\n";
        unselected = false;
        heuristicFunction = Euclidean;
        break;
        default:
        std::cout << "SORRY, YOU'VE CHOSEN A NON VALID OPTION, PLEASE TRY AGAIN\n";
        std::cout << "[0] MANHATTAN\n";
        std::cout << "[1] EUCLIDEAN\n";
        break;
    }

  }

  return heuristicFunction;

}

int main(){

int screen = 0;


std::cout << "WELCOME TO THE PATHFINDING CAR SIMULATION USING A* ALGORITHM\n";
std::cout << "CHOOSE BETWEEN: \n";
std::cout << "[0] AND GRAPHICAL MODE ( SIMULATING )\n";
std::cout << "[1] TERMINAL MODE ( TESTING )\n";

int mode = -1;
bool unselected = true;
int posX = 25;
int posY = 25;
setCellSize(20);
setFieldDimension(posX *= 20, posY *= 20);


while (unselected){

  std::cin >> mode;

switch(mode){
  case 0:
  std::cout << "SIMULATING MODE SELECTED\n";
  unselected = false;
  screen = 0;
  break;
  case 1:
  std::cout << "TESTING MODE SELECTED\n";
  unselected = false;
  gHeuristic = selectHeuristicFunction();
  screen = 1;
  break;
  default:
  std::cout << "SORRY SELECTED MODE IS NOT A VALID MODE, PLEASE TRY AGAIN: \n";
  std::cout << "[0] TERMINAL MODE ( TESTING )\n";
  std::cout << "[1] AND GRAPHICAL MODE ( SIMULATING )\n";
  break;

  }
}

if(mode == 1){
  test();
}else{


  sf::RenderWindow window(sf::VideoMode(500,500), "Autonomous Car", sf::Style::Close);

  std::vector<cScreen*> Screens;


  simulationScreen screen01;
  testScreen screen02;

  Screens.push_back(&screen01);
  Screens.push_back(&screen02);

  while (screen != -1){
    screen = Screens[screen] -> Run(window);
  }
}



}
