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

int calculateMean(std::vector<int> v){
  int sum = 0;
  for (auto element: v)
       sum += element;
  return (sum /= v.size());
}

double calculateMean(std::vector<double> v){
  double sum = 0;
  for (auto element: v)
       sum += element;
  return (sum /= v.size());
}


void test(){

bool running = true;
int currentDimension = 20;
int nTest = 10;

while (running){

  for (int percentage = 10; percentage < 100; percentage += 10){

    std::vector<int> vPath;
    std::vector<int> vGeneratedNodes;
    std::vector<double> vCpuTime;

    std::cout << "\n\n-------------------------------------------------------\n";
    std::cout << "CURRENT DIMENSION -> " << currentDimension << " x " << currentDimension << "\n";
    std::cout << "CURRENT PERCENTAGE -> " << percentage << "\n";
    std::cout << "NUMBER OF TEST -> " << nTest << "\n";

    for (int test = 0; test < nTest ; test++){
      int pathSize = 0;
      double cpuTime = 0.0f;
      int generatedNodes = 0;
      calculateParameters(currentDimension,percentage,pathSize,cpuTime,generatedNodes);
      vPath.push_back(pathSize);
      vGeneratedNodes.push_back(generatedNodes);
      vCpuTime.push_back(cpuTime);
    }

    std::cout << "PATHSIZE -> " << calculateMean(vPath) << "\n";
    std::cout << "CPU TIME -> " << calculateMean(vCpuTime) << "\n";
    std::cout << "GENERATED NODES -> " << calculateMean(vGeneratedNodes) << "\n";


  }
  std::cout << "\n\n..............................................................................\n";
  std::cout << "..............................................................................\n\n";
  currentDimension += 10;
}

}
