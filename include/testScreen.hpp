#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include "cScreen.hpp"
#include <thread>
#include <chrono>
#include <time.h>

class testScreen : public cScreen {


private:
public:
    void display(sf::RenderWindow& window, Field simulationField, autonomousCar ferrari);
    virtual int Run(sf::RenderWindow& window);
};
