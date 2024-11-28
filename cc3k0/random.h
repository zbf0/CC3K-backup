#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

void randomSort (std::vector<int>& v);

std::vector<int>* randomIntGenerator (int lowerBound, int upperBound, int n = 1, bool replacement = false ,bool sort = false);

#endif
