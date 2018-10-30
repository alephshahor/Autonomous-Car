#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"
#include "initialScreen.hpp"
#include "simulationScreen.hpp"

int main(){


sf::RenderWindow window(sf::VideoMode(500,500), "Autonomous Car", sf::Style::Close);

std::vector<cScreen*> Screens;

simulationScreen screen01;
Screens.push_back(&screen01);

int screen = 0;

while (screen != -1){
  screen = Screens[screen] -> Run(window);
}



}
