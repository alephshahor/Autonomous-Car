#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"
#include "initialScreen.hpp"
#include "simulationScreen.hpp"


int main(){

int posX, posY;
std::cout << "Introduce field X-AXIS dimension: ";
std::cin >> posX;
std::cout << "Y-AXIS dimension: ";
std::cin >> posY;

posX *= 20;
posY *= 20;

ceil(posX);
ceil(posY);

setFieldDimension(posX, posY);


sf::RenderWindow window(sf::VideoMode(posX,posY), "Autonomous Car", sf::Style::Close);

std::vector<cScreen*> Screens;

simulationScreen screen01;
Screens.push_back(&screen01);

int screen = 0;

while (screen != -1){
  screen = Screens[screen] -> Run(window);
}



}
