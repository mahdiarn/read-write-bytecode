#include "PenapisGaussian.h"

std::vector<std::vector<int>> PenapisGaussian(std::vector<std::vector<int>> input) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;
    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size(); j++) {
            outputTemp.push_back(999);
        }
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    for(std::size_t i=1; i < input.size()-1; i++) {
        for(std::size_t j=1; j < input[i].size()-2; j++) {
            output[i][j] = input[i-1][j-1] + input[i-1][j+1] + input[i+1][j-1] + input[i+1][j+1] + (2 * input[i-1][j])  + (2 * input[i][j-1])  + (2 * input[i+1][j])  + (2 * input[i][j+1]) + (4 * input[i][j]);
        }
    }

    return output;
}
