#include "cell.hpp"


Cell::Cell(float cellSize, std::pair<int,int> position):
      cellSize(cellSize),
      position(position)
      {
        blackSquare.loadFromFile("./art/black.png");
        whiteSquare.loadFromFile("./art/white.png");
        cellDrawable.setSize(sf::Vector2f(cellSize,cellSize));
        cellDrawable.setPosition(position.first, position.second);
      }

Cell::Cell(float cellSize, int posX, int posY){
      this -> cellSize = cellSize;
      position = std::make_pair(posX, posY);

      blackSquare.loadFromFile("./art/black.png");
      whiteSquare.loadFromFile("./art/white.png");
      cellDrawable.setSize(sf::Vector2f(cellSize,cellSize));
      cellDrawable.setPosition(posX, posY);
}


void Cell::setPosition(int posX, int posY){
     position.first = posX;
     position.second = posY;
}

void Cell::setPosition(std::pair<int,int> position){
    this -> position.first = position.first;
    this -> position.second = position.second;
}

void Cell::setTexture(cellObjects cellObject){

  switch(cellObject){
    case 0:
    cellDrawable.setTexture(&whiteSquare);
    break;

    case 1:
    cellDrawable.setTexture(&blackSquare);
    break;

    case 2:
    break;

    default:
    break;

  }

}

std::pair<int,int> Cell::getPosition(){
    return position;
}


void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cellDrawable);
}
