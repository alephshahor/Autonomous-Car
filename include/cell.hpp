#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.hpp"

class Cell : public sf::Drawable{

  private:

    float cellSize;
    std::pair<int,int> position; // pair<posX,posY>
    sf::RectangleShape cellDrawable;
    sf::Texture whiteSquare;
    sf::Texture blackSquare;
    sf::Texture goalSquare;
    sf::Texture optimalSquare;
    CellObjects cellType;

    bool occupied;

    // This function allows us to draw the cell using a nicer syntax
    // window.draw(cell) instead of cell.draw(window).
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:

    // Constructors

    Cell(float cellSize, std::pair<int,int> position,  CellObjects cellType, bool occupied);
    Cell(float cellSize, int posX, int posY, CellObjects cellType, bool occupied);

    // Setters

    void setPosition(int posX, int posY);
    void setPosition(std::pair<int,int> position);
    void occupy();
    void release();

    // Getters

    std::pair<int,int> getPosition();


    // This function sets the correspond texture depending on whether the
    // cell is dead or alive.
    void setTexture(CellObjects CellObject);

    bool isOccupied();


};
