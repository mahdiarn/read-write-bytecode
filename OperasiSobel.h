#ifndef OPERASISOBEL_H
#define OPERASISOBEL_H
#include <vector>
#include <cmath>

std::vector<std::vector<int>> SobelX(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> SobelY(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> Sobel(std::vector<std::vector<int>> input, double treshold);


#endif // OPERASISOBEL_H
