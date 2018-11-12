#include "test.hpp"

bool calculateParameters(int currentDimension, int percentage, int& pathSize, double& cpuTime, int& generatedNodes){
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

  if (finalNode != NULL)
      return true;
  else return false;

  }

int calculateMean(std::vector<int> v){
  int sum = 0;
  for (auto element: v)
       sum += element;
  return (sum / v.size());
}

double calculateMean(std::vector<double> v){
  double sum = 0;
  for (auto element: v)
       sum += element;
  return (sum / v.size());
}

int calculateSuccess(std::vector<bool> v){
  int sum = 0;
  for (auto element: v)
      if (element)
          sum++;
  return sum;
}

void test(){

bool running = true;
int currentDimension = 20;
int nTest = 10;

while (running){

  int printingCounter = 0;
  std::cout << "\n\n";
  std::cout << std::left << std::setfill(' ') << "  "
            << std::setw(11) << "DIMENSION"
            << std::setw(11) << "OBSTACLES"
            << std::setw(13) << "PATH_LENGHT"
            << std::setw(10) << "CPU_TIME"
            << std::setw(17) << "GENERATED_NODES"
            << std::setw(11) << "SUCCESS_RATIO" << "\n";

  for (int percentage = 10; percentage < 55; percentage += 5){

    std::vector<int> vPath;
    std::vector<int> vGeneratedNodes;
    std::vector<double> vCpuTime;
    std::vector<bool> vSuccess;


    for (int test = 0; test < nTest ; test++){
      int pathSize = 0;
      double cpuTime = 0.0f;
      int generatedNodes = 0;
      vSuccess.push_back(calculateParameters(currentDimension,percentage,pathSize,cpuTime,generatedNodes));

      if (pathSize != 0)
      vPath.push_back(pathSize);
      if (generatedNodes != 0.0)
      vGeneratedNodes.push_back(generatedNodes);
      if (pathSize != 0)
      vCpuTime.push_back(cpuTime);

    }

    std::cout << std::left << std::setfill(' ') << "    "
              << currentDimension << "x"
              << std::setw(9) << currentDimension
              << percentage + printingCounter
              << std::setw(10) << "%"
              << std::setw(10) << calculateMean(vPath)
              << std::setw(15) << calculateMean(vCpuTime)
              << std::setw(15) << calculateMean(vGeneratedNodes)
              << calculateSuccess(vSuccess) << "/" << vSuccess.size() << "\n";

    printingCounter += 5;

  }
  std::cout << "\n\n..............................................................................\n";
  std::cout << "..............................................................................\n\n";
  currentDimension += 10;
}

}
