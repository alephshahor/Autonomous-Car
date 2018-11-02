#include "field.hpp"

Field::Field(int width, int height, float cellSize):
       cellSize(cellSize),
       vectorOfCells(),
       fieldDimension(std::make_pair(width,height))
       {

         for (int i = 0; i < width / cellSize; i++){
             std::vector<Cell> vCells;
             for (int j = 0; j < height / cellSize; j++){
               vCells.push_back(Cell(cellSize, cellSize*i, cellSize*j, Empty, false));
              }
               vectorOfCells.push_back(vCells);
         }

         for (int i = 0; i < width / cellSize; i++){
             for (int j = 0; j < height / cellSize; j++){
               vectorOfCells[i][j].setTexture(Empty);
             }
         }

       }

Field::Field(std::pair<int,int> fieldDimension, float cellSize):
        cellSize(cellSize),
        vectorOfCells(),
        fieldDimension(fieldDimension)
        {

          for (int i = 0; i < fieldDimension.first / cellSize; i++){
              std::vector<Cell> vCells;
              for (int j = 0; j < fieldDimension.second / cellSize; j++){
                vCells.push_back(Cell(cellSize, cellSize*i, cellSize*j, Empty, false));
              }
                vectorOfCells.push_back(vCells);
          }

          /* This is necessary because when you use push_back you're actually
          creating a copy of the object you're inserting so you lose the
          texture reference*/
          for (int i = 0; i < fieldDimension.first / cellSize; i++){
              for (int j = 0; j < fieldDimension.second / cellSize; j++){
                vectorOfCells[i][j].setTexture(Empty);
              }
          }


        }

Cell Field::getCell(int posX, int posY){
        return vectorOfCells[posX][posY];
}

int Field::getWidth(){
  return fieldDimension.first / cellSize;
}

int Field::getHeight(){
  return fieldDimension.second / cellSize;
}

void Field::changeCellState(int posX, int posY){

    posX /= cellSize;
    posY /= cellSize;

    if (!vectorOfCells[posX][posY].isOccupied()){
        vectorOfCells[posX][posY].occupy();
        vectorOfCells[posX][posY].setTexture(Obstacle);
    }else{
        vectorOfCells[posX][posY].release();
        vectorOfCells[posX][posY].setTexture(Empty);
      }
}


std::vector<Node> Field::calculateChilds(Node* targetNode){

    std::vector<Node> nodeChilds;
    std::pair<int,int> actualPos = targetNode -> getPosition();

    if ((actualPos.first != 0) && (!vectorOfCells[actualPos.first - 1][actualPos.second].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first - 1, actualPos.second), targetNode));

    if ((actualPos.first != vectorOfCells.size() - 1) && (!vectorOfCells[actualPos.first + 1][actualPos.second].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first + 1, actualPos.second), targetNode));


    if ((actualPos.second != 0) && (!vectorOfCells[actualPos.first][actualPos.second - 1].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first, actualPos.second - 1), targetNode));

    if ((actualPos.second != vectorOfCells[0].size() - 1) && (!vectorOfCells[actualPos.first][actualPos.second + 1].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first, actualPos.second + 1), targetNode));

    return nodeChilds;
}


int Field::calculateHeuristic(Node targetNode, std::pair<int,int> finalPos){

      std::pair<int,int> nodePos = targetNode.getPosition();
      int heuristicValue = abs(nodePos.first - finalPos.first) + abs(nodePos.second - finalPos.second);
      return heuristicValue;

}

int Field::calculateFunction(Node targetNode, std::pair<int,int> finalPos, int actualWeight){
      return calculateHeuristic(targetNode, finalPos) + actualWeight;
}


// TODO Check the boundaries of the field while calculating the childs.

void Field::calculateOptimalRoute(std::pair<int,int> initialPos, std::pair<int,int> finalPos){


  int actualWeight = 1;
  Node rootNode(initialPos, NULL);

  Node* actualNode = &rootNode;
  std::vector<Node> vectorOfNodes;
  std::deque<Node> nodeDeque;

  nodeDeque.push_back(rootNode);

  // While the actualNode is not the target node.
  while ((actualNode -> getPosition().first != finalPos.first) && (actualNode -> getPosition().second != finalPos.second)){

  // We calculate actualNode childs
  std::vector<Node> nodeChilds = calculateChilds(actualNode);

  // Then for each node we calculate its function
  // And also we set them as actualNode childs
  for (int i = 0; i < nodeChilds.size(); i++){
       std::cout << "Introducing node with PosX: " << nodeChilds[i].getPosition().first << " PosY: " << nodeChilds[i].getPosition().second << "\n";
       nodeChilds[i].setData(calculateFunction(nodeChilds[i], finalPos, actualWeight));
       actualNode -> setChild(&nodeChilds[i]);
  }



  // Now we push them sorted in a deque
  // TODO: Im pushing multiple times the same node.

  /*for (int i = 0; i < nodeChilds.size(); i++){
    Node nodeToPush = nodeChilds[i];
    for (int j = 0; j < nodeChilds.size(); j++){
        if (nodeChilds[i].getData() < nodeChilds[j].getData())
            nodeToPush = nodeChilds[i];
        else nodeToPush = nodeChilds[j];
    }
  }*/

  for (int i = 0; i < nodeChilds.size(); i++)
      nodeDeque.push_back(nodeChilds[i]);

  // Pops the node that was being expanded
  nodeDeque.pop_front();

  // Sort the rest of the nodes
  for (int i = 0; i < nodeDeque.size(); i++){
    int minValue = nodeDeque[i].getData();
    int minIndex = -1;
    for (int j = 0; j < nodeDeque.size(); j++){
      if (minValue > nodeDeque[j].getData()){
          minValue = nodeDeque[j].getData();
          minIndex = j;
        }
    }

    if ((minIndex != -1) && (minValue != nodeDeque[0].getData())){
        Node nodeTemp = nodeDeque[0];
        nodeDeque[0] = nodeDeque[minIndex];
        nodeDeque[minIndex] = nodeTemp;
    }

  }

  std::cout << "Front node has PosX : " << nodeDeque.front().getPosition().first << " PosY: " << nodeDeque.front().getPosition().second << "\n";

  //std::cout << "Front node has PosX : " << nodeDeque.front().getPosition().first << " PosY: " << nodeDeque.front().getPosition().second << "\n";

  // Front node of the deque will be the actualNode to expand
  actualNode = &nodeDeque.front();



  actualWeight++;

  }

  rootNode.printDescendents();




}
