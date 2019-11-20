#include "OperasiPrewitt.h"

std::vector<std::vector<int>> PrewittX(std::vector<std::vector<int>> input) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;

    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size(); j++) {
            outputTemp.push_back(0);
        }
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    for(std::size_t i=1; i < input.size()-1; i++) {
        for(std::size_t j=1; j < input[i].size()-2; j++) {
            output[i][j] = (-1 * input[i-1][j-1]) + (-1 * input[i][j-1]) + (-1 * input[i+1][j-1]) + input[i-1][j+1] + (1 * input[i][j+1]) + (1 * input[i+1][j+1]);
        }
    }

    return output;
}

std::vector<std::vector<int>> PrewittY(std::vector<std::vector<int>> input) {
    std::vector<std::vector<int>> output;
    std::vector<int> outputTemp;

    for(std::size_t i=0; i < input.size(); i++) {
        for(std::size_t j=0; j < input[i].size(); j++) {
            outputTemp.push_back(0);
        }
        output.push_back(outputTemp);
        outputTemp.clear();
    }

    for(std::size_t i=1; i < input.size()-1; i++) {
        for(std::size_t j=1; j < input[i].size()-2; j++) {
            output[i][j] = input[i-1][j-1] + (1 * input[i-1][j]) + input[i-1][j+1] + (-1 * input[i+1][j-1]) + (-1 * input[i+1][j]) + (-1 * input[i+1][j+1]);
        }
    }

    return output;
}

std::vector<std::vector<int>> Prewitt(std::vector<std::vector<int>> input, double treshold) {
    std::vector<std::vector<int>> Sx = PrewittX(input);
    std::vector<std::vector<int>> Sy = PrewittY(input);
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

    for(std::size_t i=1; i < input.size()-1; i++) {
        for(std::size_t j=1; j < input[i].size()-2; j++) {
            value = std::sqrt((Sx[i][j] * Sx[i][j]) + (Sy[i][j] * Sy[i][j]));
            if (value >= treshold) {
                output[i][j] = 1;
            } else {
                output[i][j] = 0;
            }
        }
    }

    return output;
}
