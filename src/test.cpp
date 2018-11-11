#include "test.hpp"

void calculateParameters(int currentDimension, int percentage, int& pathSize, double& cpuTime, int& generatedNodes){
  Field simulationField(currentDimension * gCellSize, currentDimension * gCellSize, float(getCellSize()));
  std::pair<int,int> carDimension = std::make_pair(getCellSize(),getCellSize());
  std::pair<int,int> carPosition = std::make_pair(10,10);
  autonomousCar ferrari(carDimension, carPosition);

  // Reset terrain state
  simulationField.reset();
  // Generate random terrain
  simulationField.generateRandomTerrain(percentage);
  if (simulationField.getCell(carPosition.first, carPosition.second).isOccupied()){
      simulationField.getCell(carPosition.first, carPosition.second).release();
      simulationField.getCell(carPosition.first, carPosition.second).setTexture(Empty);
  }

  // Generate random goal position
  std::pair<int,int> finalPos = simulationField.generateRandomGoal();
  simulationField.changeCellState(finalPos.first * gCellSize , finalPos.second * gCellSize, Goal);

generatedNodes = 0;
    // Calculate the optimal route
clock_t start = clock();
std::list<Node> cellRoute = simulationField.calculateOptimalRoute(ferrari.getPosition(),finalPos,generatedNodes, gHeuristic);
clock_t stop = clock();
cpuTime = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
// If the algorithm find a solution, obtain the final node direction
Node* finalNode = NULL;
for (auto node: cellRoute)
  if (node.getPosition().first == finalPos.first && node.getPosition().second == finalPos.second)
      finalNode = &node;


// Count how long the path is from the beginning to the final node
pathSize = 0;
if (finalNode != NULL){
  pathSize++;
  while (finalNode -> getParent() != NULL){
      pathSize++;
      finalNode = finalNode -> getParent();
    }
  }
}


void test(){


int pathSize = 0;
double cpuTime = 0.0f;
int generatedNodes = 0;

for (int indice = 0; indice < 20; indice++){
  calculateParameters(20,10,pathSize,cpuTime,generatedNodes);

  std::cout << "PATHSIZE -> " << pathSize << "\n";
  std::cout << "CPU TIME -> " << cpuTime << "\n";
  std::cout << "GENERATED NODES -> " << generatedNodes << "\n";
  }
}
