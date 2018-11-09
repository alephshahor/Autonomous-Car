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

void Field::changeCellState(int posX, int posY, CellObjects cellObject){

    posX /= cellSize;
    posY /= cellSize;

    if (!vectorOfCells[posX][posY].isOccupied()){
         vectorOfCells[posX][posY].occupy();
    }else if (cellObject != Visited){
          vectorOfCells[posX][posY].release();
          cellObject = Empty;
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


int Field::calculateHeuristic(Node targetNode, std::pair<int,int> finalPos){

      std::pair<int,int> nodePos = targetNode.getPosition();
      int heuristicValue = abs(nodePos.first - finalPos.first) + abs(nodePos.second - finalPos.second);
      return heuristicValue;

}

int Field::calculateFunction(Node targetNode, std::pair<int,int> finalPos){
      return calculateHeuristic(targetNode, finalPos) + (targetNode.getParent() -> getWeight() + 1);
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


 std::list<Node> Field::calculateOptimalRoute(std::pair<int,int> initialPos, std::pair<int,int> finalPos){

   std::list<Node> nodeList;
   std::list<Node*> closedList;
   std::list<Node*> openList;

   Node rootNode(initialPos, 0, NULL);
   Node* actualNode = &rootNode;
   openList.push_back(actualNode);

   int contador = 0;


   int iterations = 0;
   bool notFound = true;
   while(!openList.empty() && notFound){


     Node* minimumNode = findMinimumNode(openList);

     std::vector<Node> nodeChilds = calculateChilds(minimumNode);

     for (auto node: nodeChilds)
          nodeList.push_back(node);


       std::list<Node>::iterator beginning = std::find(nodeList.begin(), nodeList.end(), nodeChilds[0]);

       for (std::list<Node>::iterator node = beginning; node != nodeList.end(); node++){

       if (node -> getPosition().first == finalPos.first && node -> getPosition().second == finalPos.second){
           notFound = false;
           break;
       }else{
          node -> setData(calculateFunction((*node), finalPos));
          node -> setWeight(node -> getParent() -> getWeight() + 1);
       }

       if((!lowerEqualExist(openList, (*node))) && (!lowerEqualExist(closedList, (*node)))){
          openList.push_back(&(*node));
       }

     }
        closedList.push_back(minimumNode);

        iterations++;
   }

     return nodeList;

 }


/*
 std::list<Node> Field::calculateOptimalRoute(std::pair<int,int> initialPos, std::pair<int,int> finalPos){

  int nodesIterator = 0;
  Node rootNode(initialPos, 0, NULL);

  Node* actualNode = &rootNode;

  std::list<Node> nodeList;
  std::list<Node*> nodeQueue;

  nodeQueue.push_back(actualNode);

  int itCounter =  0;

  // While the actualNode is not the target node.
  // (actualNode -> getPosition().first != finalPos.first) || (actualNode -> getPosition().second != finalPos.second)
  while ( (actualNode -> getPosition().first != finalPos.first) || (actualNode -> getPosition().second != finalPos.second)){

  // We calculate actualNode childs
  std::vector<Node> nodeChilds = calculateChilds(actualNode);

  // We push all the nodes  in the list
  for (auto node : nodeChilds)
      nodeList.push_back(node);


  // This iterator 'tries' to find the last new node inserted in the nodeList
  std::list<Node>::iterator listIterator = std::find(nodeList.begin(), nodeList.end(), *(nodeChilds.begin()));

  std::list<Node>::iterator listIterator_ = listIterator;

  for (std::list<Node>::iterator it = listIterator_; it != nodeList.end(); it++){
    it -> setData(calculateFunction((*it), finalPos));
    it -> setWeight(it -> getParent() -> getWeight() + 1);
    actualNode -> setChild(&(*it));
  }


  listIterator_ = listIterator;


  // We push in the queue the new nodes.
  for (std::list<Node>::iterator it = listIterator; it != nodeList.end(); it++){
      nodeQueue.push_back(&(*it));
  }

  // We actualize the iterator
  listIterator = nodeList.end();

  // We pop of the queue the current node being explored
  nodeQueue.pop_front();



  // We sort the list
  nodeQueue.sort([](Node* & a, Node* & b) { return a -> getData() < b -> getData(); });

  eliminateDuplicates(nodeQueue);


  // Front node of the deque will be the actualNode to expand
  actualNode = nodeQueue.front();

  //std::cout << "Front node has PosX : " << nodeQueue.front() -> getPosition().first << " PosY: " << nodeQueue.front() -> getPosition().second << " and data: " << nodeQueue.front() -> getData() << "\n";
  itCounter++;
  }

  std::vector<Node*> optimalNodeRoute = actualNode -> getRoute();

  std::vector<Cell> optimalCellRoute;
  for (auto node : optimalNodeRoute){
       Cell cell = getCell(node -> getPosition().first, node -> getPosition().second);
       optimalCellRoute.push_back(cell);
     }
//  return nodeList;


}*/
