#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "common.hpp"

class Cell : public sf::Drawable{

  private:

    float cellSize;
    std::pair<int,int> position; // pair<posX,posY>
    sf::RectangleShape cellDrawable;
    sf::Texture whiteSquare;
    sf::Texture blackSquare;
    sf::Texture goalSquare;
    std::vector <sf::Texture> textureVector;
    cellObjects cellType;

    bool occupied;

    // This function allows us to draw the cell using a nicer syntax
    // window.draw(cell) instead of cell.draw(window).
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:

    // Constructors

    Cell(float cellSize, std::pair<int,int> position,  cellObjects cellType,  bool occupied);
    Cell(float cellSize, int posX, int posY,  cellObjects cellType,  bool occupied);

    // Setters

    void setPosition(int posX, int posY);
    void setPosition(std::pair<int,int> position);
    void occupy();
    void release();

    // Getters

    std::pair<int,int> getPosition();


    // This function sets the correspond texture depending on whether the
    // cell is dead or alive.
    void setTexture(cellObjects cellObject);

    bool isOccupied();


};
