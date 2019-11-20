#ifndef OPERASISOBEL_H
#define OPERASISOBEL_H
#include <vector>
#include <cmath>

std::vector<std::vector<int>> PrewittX(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> PrewittY(std::vector<std::vector<int>> input);

std::vector<std::vector<int>> Prewitt(std::vector<std::vector<int>> input, double treshold);


#endif // OPERASISOBEL_H
