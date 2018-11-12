#pragma once
#include <iostream>
#include <vector>
#include "cell.hpp"
#include "field.hpp"
#include "common.hpp"
#include "car.hpp"
#include <thread>
#include <chrono>
#include <time.h>
#include <ctime>
#include <iomanip>

void test();
int calculateMean(std::vector<int> v);
double calculateMean(std::vector<double> v);
int calculateSuccess(std::vector<bool> v);
bool calculateParameters(int currentDimension, int percentage, int& pathSize, double& cpuTime, int& generatedNodes);
