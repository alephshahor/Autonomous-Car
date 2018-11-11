#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "cScreen.hpp"

class initialScreen : public cScreen {


private:
public:
    virtual int Run(sf::RenderWindow& window);
};
