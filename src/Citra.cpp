#include <iostream>
#include <string>
#include <vector>

#include "Citra.h"
#include "File.h"

Citra::Citra() {
    this->width = 0;
    this->height = 0;
}

void Citra::loadFile(std::vector<unsigned char> byteFile, int fileType) {
    std::vector<unsigned char> buffer;
    bool flag = true;
    bool widthFound = false;
    std::cout << "Konstruktor\n";
    std::cout << "filetype: " << fileType << std::endl;
    for (int i = 0; i<byteFile.size(); i++) {
        if (byteFile.at(i) == '6'){
            std::cout << byteFile.at(i) << " ";
        }
    }
    switch(fileType) {
        case 1:
            int start;
            int end;
            for(int i = 2;i<byteFile.size();i++) {
                if (flag){
                    if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                        start = i;
                        buffer.push_back(byteFile.at(i));
                        widthFound = true;
                    }
                    if (((byteFile.at(i+1) == 0x0a) || (byteFile.at(i+1) == 0x20)) && (widthFound)) {
                        end = i;
                        flag = false;
                    }
                }
            }
            for(int i = 0;i<buffer.size();i++) {
                this->width = this->width * 10;
                this->width = this->width + (buffer.at(i) - 48);
            }
            break;
        case 2:
            std::cout << "\n";
            break;
        case 3:
            std::cout << "\n";
            break;
        case 4:
            std::cout << "\n";
            break;
        case 0:
        default:
            std::cout << "\n";
    }
}

void Citra::printCitra() {
    if (this->kanal.size() == 1)
        std::cout << "satu kanal\n";
    if (this->kanal.size() == 3)
        std::cout << "tiga kanal\n";
}

unsigned long long Citra::getWidth() {
    return this->width;
}

unsigned long long Citra::getHeight() {
    return this->height;
}