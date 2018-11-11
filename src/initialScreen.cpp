#include "initialScreen.hpp"


int initialScreen::Run(sf::RenderWindow& window){

    sf::Texture iScreenTexture;
    sf::RectangleShape iScreenDrawable;

    iScreenTexture.loadFromFile("./art/mainscreen.png");
    iScreenDrawable.setSize(sf::Vector2f(500.0f,500.0f));
    iScreenDrawable.setPosition(0,0);
    iScreenDrawable.setTexture(&iScreenTexture);


    //window.clear();
    while (true){
    window.draw(iScreenDrawable);
    window.display();
  }

}
