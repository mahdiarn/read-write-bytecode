#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "OperasiGradien.h"

void printVector2D(std::vector<std::vector<int>> input) {
    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size()-1; j++) {
            std::cout << input[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> GradX(std::vector<std::vector<int>> input) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;
    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size()-1; j++) {
            outputTemp.push_back(input[i][j+1] - input[i][j]);
        }
        outputTemp.push_back(-1);
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    return output;
}

std::vector<std::vector<int>> GradY(std::vector<std::vector<int>> input) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;
    for(std::size_t i=0; i < input.size()-1; i++) {
        for(std::size_t j=0; j < input[i].size(); j++) {
            outputTemp.push_back(input[i+1][j] - input[i][j]);
        }
        output.push_back(outputTemp);
        outputTemp.clear();
    }
    for(std::size_t j=0; j < input[0].size(); j++) {
        outputTemp.push_back(-1);
    }
    output.push_back(outputTemp);

    return output;
}

std::vector<std::vector<int>> edgeGradient(std::vector<std::vector<int>> input, double treshold) {
    std::vector<std::vector<int>> Gx = GradX(input);
    std::vector<std::vector<int>> Gy = GradY(input);
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;
    double value;
    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size()-1; j++) {
            value = sqrt((Gx[i][j] * Gx[i][j]) + (Gy[i][j] * Gy[i][j]));
            if (value >= treshold) {
                outputTemp.push_back(1);
            } else {
                outputTemp.push_back(0);
            }

        }
        outputTemp.push_back(-1);
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    return output;
}
