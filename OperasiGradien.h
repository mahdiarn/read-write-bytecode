#ifndef OPERASIGRADIEN_H
#define OPERASIGRADIEN_H

#include <vector>

void printVector2D(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> GradX(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> GradY(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> edgeGradient(std::vector<std::vector<int>> input, double treshold);

#endif // OPERASIGRADIEN_H

