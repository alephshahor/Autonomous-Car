#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"

class simulationScreen : public cScreen {


private:
public:
    virtual int Run(sf::RenderWindow& window);

};
