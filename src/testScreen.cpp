#include "testScreen.hpp"

void testScreen::display(sf::RenderWindow& window, Field simulationField, autonomousCar ferrari){

  std::pair<int,int> carPos = ferrari.getPosition();
  window.clear();
  for (int i = 0; i < simulationField.getWidth(); i++){
    for (int j = 0; j < simulationField.getHeight(); j++){
      if ((i == carPos.first) && (j == carPos.second))
           window.draw(ferrari);
      else window.draw(simulationField.getCell(i,j));
      }
    }


  window.display();
}

int testScreen::Run(sf::RenderWindow& window){


std::pair<int,int> carDimension = std::make_pair(getCellSize(),getCellSize());
std::pair<int,int> carPosition = std::make_pair(10,10);
std::pair<int,int> finalPos = std::make_pair(3,3);
autonomousCar ferrari(carDimension, carPosition);

CellObjects currentCellObject = Obstacle;

bool running = true;
bool pause = false;
bool optimalRoute = false;
bool sequentialMode = false;

int currentDimension = 20;
int cellSize = getCellSize();
int generatedNodes = 0;
int pathSize = 0;
double cpuTime;

std::vector<int> vGeneratedNodes;
std::vector<int> vPaths;
std::vector<double> vCpuTime;

while (running){

  Field simulationField(currentDimension * cellSize , currentDimension * cellSize , float(getCellSize()));

  for (int percentage = 10; percentage < 100; percentage +=10 ){

    vGeneratedNodes.erase(vGeneratedNodes.begin(), vGeneratedNodes.end());
    vPaths.erase(vPaths.begin(), vPaths.end());
    vCpuTime.erase(vCpuTime.begin(), vCpuTime.end());

    for (int prueba =  0; prueba < 10; prueba++){
      cpuTime = 0.0f;

    /* Random terrain generation with new percentage*/
    simulationField.generateRandomTerrain(percentage);
                if (simulationField.getCell(carPosition.first, carPosition.second).isOccupied()){
                    simulationField.getCell(carPosition.first, carPosition.second).release();
                    simulationField.getCell(carPosition.first, carPosition.second).setTexture(Empty);
                }
    std::pair<int,int> carPos = ferrari.getPosition();
    finalPos = simulationField.generateRandomGoal();
    simulationField.changeCellState(finalPos.first * cellSize , finalPos.second * cellSize, Goal);
    //std::cout << "GOAL POSITION -> " << finalPos.first << " , " << finalPos.second << "\n";

    clock_t start = clock();
    std::list<Node> cellRoute = simulationField.calculateOptimalRoute(carPos, finalPos, generatedNodes, Manhattan);
    clock_t stop = clock();
    cpuTime = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    Node* finalNode = NULL;
    for (auto node: cellRoute){
      if (node.getPosition().first == finalPos.first && node.getPosition().second == finalPos.second)
          finalNode = &node;
      else simulationField.changeCellState(node.getPosition().first * gCellSize , node.getPosition().second * gCellSize, Visited);
        }

    if (finalNode != NULL){
    pathSize++;
    while (finalNode -> getParent() != NULL){
        pathSize++;
        finalNode = finalNode -> getParent();
        simulationField.changeCellState(finalNode -> getPosition().first * gCellSize , finalNode -> getPosition().second * gCellSize, Optimal);
    }
  }

  //TODO I've to find out why if i don't use this sleep the values pushed are bad.
  std::this_thread::sleep_for (std::chrono::seconds(1));

  /* Simulation field resetting*/
  simulationField.reset();

  vGeneratedNodes.push_back(generatedNodes);
  vPaths.push_back(pathSize);
  vCpuTime.push_back(cpuTime);

  }

  std::cout << "\nCURRENT DIMENSION -> " << currentDimension << "\n";
  std::cout << "CURRENT PERCENTAGE -> " << percentage << "\n";
  for (auto path: vPaths)
      std::cout << "PATH -> " << path << "\n";
  for (auto node: vGeneratedNodes)
      std::cout << "GENERATED NODES -> " << node << "\n";

  for (auto cpuTime: vCpuTime)
      std::cout << "CPU TIME -> " << cpuTime << "\n";
  std::cout << "------------------------------------------------\n\n";


  }

    currentDimension +=10;


}


}
