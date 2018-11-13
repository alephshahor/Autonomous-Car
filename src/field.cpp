#include "field.hpp"

Field::Field(int width, int height, float cellSize):
       cellSize(cellSize),
       vectorOfCells(),
       fieldDimension(std::make_pair(width,height))
       {
         for (int i = 0; i < width / cellSize; i++){
             std::vector<Cell> vCells;
             vCells.reserve(width / cellSize);
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

void Field::reset(){

  for (int i = 0; i < fieldDimension.first / cellSize; i++){
      for (int j = 0; j < fieldDimension.second / cellSize; j++){
        vectorOfCells[i][j].setTexture(Empty);
        vectorOfCells[i][j].release();
      }
  }

}

void Field::changeCellState(int posX, int posY, CellObjects cellObject){

    posX /= cellSize;
    posY /= cellSize;

    if (!vectorOfCells[posX][posY].isOccupied() && cellObject != Goal && cellObject != Empty){
         vectorOfCells[posX][posY].occupy();
    }else if (cellObject == Obstacle){
          vectorOfCells[posX][posY].release();
          cellObject = Empty;
    }else if (cellObject == Goal){
          vectorOfCells[posX][posY].release();
    }

    switch(cellObject){
      case 0:
      vectorOfCells[posX][posY].setTexture(Empty);
      break;

      case 1:
      vectorOfCells[posX][posY].setTexture(Obstacle);
      break;

      case 2:
      vectorOfCells[posX][posY].setTexture(Goal);
      break;

      case 3:
      vectorOfCells[posX][posY].setTexture(Optimal);
      break;

      case 4:
      vectorOfCells[posX][posY].setTexture(Visited);
      break;

      default:
      std::cerr << "Failed trying to change texture\n";
      break;

    }

}


std::vector<Node> Field::calculateChilds(Node* targetNode){

    std::vector<Node> nodeChilds;
    std::pair<int,int> actualPos = targetNode -> getPosition();

    if ((actualPos.first != 0) && (!vectorOfCells[actualPos.first - 1][actualPos.second].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first - 1, actualPos.second), 0, targetNode, false));

    if ((actualPos.first != vectorOfCells.size() - 1) && (!vectorOfCells[actualPos.first + 1][actualPos.second].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first + 1, actualPos.second), 0, targetNode, false));


    if ((actualPos.second != 0) && (!vectorOfCells[actualPos.first][actualPos.second - 1].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first, actualPos.second - 1), 0, targetNode, false));

    if ((actualPos.second != vectorOfCells[0].size() - 1) && (!vectorOfCells[actualPos.first][actualPos.second + 1].isOccupied()))
        nodeChilds.push_back(Node(std::make_pair(actualPos.first, actualPos.second + 1), 0, targetNode, false));

    return nodeChilds;
}


int Field::calculateHeuristic(Node targetNode, std::pair<int,int> finalPos, Heuristic heuristicFunction){

      std::pair<int,int> nodePos = targetNode.getPosition();
      int heuristicValue = 0;

      switch(heuristicFunction){
        case 0:
        heuristicValue = abs(nodePos.first - finalPos.first) + abs(nodePos.second - finalPos.second);
        break;
        case 1:
        heuristicValue = sqrt(pow(abs(nodePos.first - finalPos.first),2) + pow(abs(nodePos.second - finalPos.second),2));
        break;
        default:
        std::cout << "Failed to calculate Heuristic Function\n";
        break;
      }

      return heuristicValue;

}

int Field::calculateFunction(Node targetNode, std::pair<int,int> finalPos, Heuristic heuristicFunction){

      int nodeWeight = 0;
      if (targetNode.getParent() != NULL)
          nodeWeight = targetNode.getParent() -> getWeight() + 1;

      return calculateHeuristic(targetNode, finalPos, heuristicFunction) + nodeWeight;
}

bool Field::nodesAreEqual(Node* nodeA, Node* nodeB){
  if (nodeA -> getPosition().first != nodeB -> getPosition().first){
    return false;
    }else if (nodeA -> getPosition().second != nodeB-> getPosition().second){
        return false;
    }else if (nodeA -> getData() != nodeB -> getData()){
        return false;
    }else if (nodeA -> getWeight() != nodeB -> getWeight()){
        return false;
    }else return true;
}


void Field::eliminateDuplicates(std::list<Node*>& nodeQueue){
  // Beginning of the method.

    std::list<Node*>::iterator targetNode = nodeQueue.begin();

    while (targetNode != nodeQueue.end()){

    bool coincidences = true;
    while(coincidences){

      coincidences = false;
      std::list<Node*>::iterator it = targetNode;
      it++;


      while (it != nodeQueue.end()){
        //std::cout << "Iterating\n";
        //std::cout << "It node = ";
        //(*it) -> printInfo();
        //std::cout << "Target node = ";
        //(*targetNode) -> printInfo();

        if ( nodesAreEqual((*it),(*targetNode)) ){
             //std::cout << "Erasing\n";
             nodeQueue.erase(it);
             coincidences = true;
             break;
        }else it++;
      }

    }
      targetNode++;
  }
}

// TODO Check the boundaries of the field while calculating the childs.

Node* Field::findMinimumNode(std::list<Node*>& openList){
   std::list<Node*>::iterator itMin = openList.begin();
   Node* minimumNode = (*itMin);

   for (std::list<Node*>::iterator it = openList.begin(); it != openList.end(); it++){
     if ((*it) -> getData() < minimumNode -> getData()){
         minimumNode = *it;
         itMin = it;
       }
   }

   openList.erase(itMin);

   return minimumNode;

 }

bool Field::lowerEqualExist(std::list<Node*> openList, Node node){
      Node* targetNode = &node;
      for (std::list<Node*>::iterator it = openList.begin(); it != openList.end(); it++){
          if (((*it) -> getPosition().first == targetNode -> getPosition().first) && ((*it) -> getPosition().second == targetNode -> getPosition().second)){
              if ((*it) -> getData() <= targetNode -> getData())
                 return true;
          }
      }

      return false;
 }


bool Field::lowerEqualExist(std::list<Node> closedList, Node node){
      for (std::list<Node>::iterator it = closedList.begin(); it != closedList.end(); it++){
          if ((it -> getPosition().first == node.getPosition().first) && (it -> getPosition().second == node.getPosition().second)){
              if (it -> getData() <= node.getData())
                 return true;
          }
      }

      return false;
 }


 std::list<Node> Field::calculateOptimalRoute(std::pair<int,int> initialPos, std::pair<int,int> finalPos, int& generatedNodes, Heuristic heuristicFunction){

   std::list<Node> nodeList;
   std::list<Node*> closedList;
   std::list<Node*> openList;

   Node rootNode(initialPos, 0, NULL);
   nodeList.push_back(rootNode);
   openList.push_back(&nodeList.front());


   int iterations = 0;
   bool notFound = true;
   while(!openList.empty() && notFound){

     // Find the minimum node and pops it out of the open list
     Node* minimumNode = findMinimumNode(openList);

     // Calculate its childs
     std::vector<Node> nodeChilds = calculateChilds(minimumNode);

     for (auto node: nodeChilds)
          nodeList.push_back(node);


       std::list<Node>::iterator beginning = nodeList.end();

      // For every child calculated
       if (!nodeChilds.empty())
       beginning = std::find(nodeList.begin(), nodeList.end(), nodeChilds[0]);

       for (std::list<Node>::iterator node = beginning; node != nodeList.end(); node++){
       // If it founds the target node, stop searching.
       if (node -> getPosition().first == finalPos.first && node -> getPosition().second == finalPos.second){
           notFound = false;

           break;
       }else{
         // Otherwise set its data and parent to the current minimum node
          node -> setData(calculateFunction((*node), finalPos, heuristicFunction));

          if (node -> getParent() != NULL)
          node -> setWeight(node -> getParent() -> getWeight() + 1);


       }
       // If it doesn't exist a similar node in the open / closed list, push it into the open list.
       if((!lowerEqualExist(openList, (*node))) && (!lowerEqualExist(closedList, (*node)))){

          openList.push_back(&(*node));

       }

     }
      // Push the current minimum node into the closed list
        closedList.push_back(minimumNode);

        iterations++;
   }

    // This variable holds the number of nodes generated
    generatedNodes = nodeList.size();

     return nodeList;

 }

std::pair<int,int> Field::uniToBidimensional(int rangePos){

  int xPos,yPos;

  if (rangePos < (fieldDimension.first / cellSize)){
    xPos = 0;
    yPos = rangePos;
  }else{
    xPos = rangePos / (fieldDimension.first / cellSize);
    yPos = rangePos - ((fieldDimension.first / cellSize) * xPos);
  }

   return std::make_pair(xPos,yPos);


}

void Field::generateRandomTerrain(int percentage){

  int range = pow((fieldDimension.first / cellSize), 2);
  int nOccupyCells = (percentage * range) / 100;

  srand((unsigned)time(0));
  for (int i = 0; i < nOccupyCells; i++){
    int rangePos = (rand() % range) + 0;
    std::pair<int,int> targetPosition = uniToBidimensional(rangePos);
    vectorOfCells[targetPosition.first][targetPosition.second].occupy();
    vectorOfCells[targetPosition.first][targetPosition.second].setTexture(Obstacle);
  }

}


std::pair<int,int> Field::generateRandomGoal(){

  int range = pow((fieldDimension.first / cellSize), 2);
  int rangePos = (rand() % range) + 0;
  std::pair<int,int> goalPosition = uniToBidimensional(rangePos);
  return goalPosition;

}
