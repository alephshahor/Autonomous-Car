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


struct lex_compare{
  bool operator() (const Node* targetNode1, const Node* targetNode2) const{
    return targetNode1 < targetNode2;
  }
};



int main(){


int posX, posY;
std::cout << "Introduce field X-AXIS dimension: ";
std::cin >> posX;
std::cout << "Y-AXIS dimension: ";
std::cin >> posY;


if ((posX == posY) && (posX < 100)){
  posX *= 2;
  posY *= 2;
  setCellSize(20);
}else if ((posX == posY) && (posX >= 100)){
  posX *= 10;
  posY *= 10;
  setCellSize(10);
}



ceil(posX);
ceil(posY);

setFieldDimension(posX, posY);


sf::RenderWindow window(sf::VideoMode(500,500), "Autonomous Car", sf::Style::Close);

std::vector<cScreen*> Screens;

simulationScreen screen01;
Screens.push_back(&screen01);

int screen = 0;

while (screen != -1){
  screen = Screens[screen] -> Run(window);
}



}
