#include "OperasiRoberts.h"

std::vector<std::vector<int>> Roberts(std::vector<std::vector<int>> input, double treshold) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;
    double value;

    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size(); j++) {
            outputTemp.push_back(0);
        }
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    for(std::size_t i=0; i < input.size()-1; i++) {
        for(std::size_t j=0; j < input[i].size()-2; j++) {
            value = std::abs(input[i][j] - input[i+1][j+1]) + std::abs(input[i][j+1] - input[i+1][j]);
            if (value >= treshold) {
                output[i][j] = 1;
            } else {
                output[i][j] = 0;
            }
        }
    }

    return output;
}
