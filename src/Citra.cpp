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
    std::vector<std::vector<unsigned char>> bufferCitra;
    bool flagWidth = true;
    bool flagHeight = true;
    bool widthFound = false;
    bool heightFound = false;
    int startWidth = 2;
    int endWidth;
    int startHeight;
    int endHeight;
    int startData;
    int counter = 0;
    std::cout << "Konstruktor\n";
    std::cout << "filetype: " << fileType << std::endl;
    for (int i = 0; i<byteFile.size(); i++) {
        if (byteFile.at(i) == '6'){
            std::cout << byteFile.at(i) << " ";
        }
    }
    switch(fileType) {
        case 1:
            this->max_value = 1;
            for(int i = startWidth;i<byteFile.size();i++) {
                if (flagWidth) {
                    if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                        startWidth = i;
                        buffer.push_back(byteFile.at(i));
                        widthFound = true;
                    }
                    if (((byteFile.at(i+1) == 0x0a) || (byteFile.at(i+1) == 0x20)) && (widthFound)) {
                        endWidth = i;
                        flagWidth = false;
                    }
                }
            }
            for(int i = 0;i<buffer.size();i++) {
                this->width = this->width * 10;
                this->width = this->width + (buffer.at(i) - 48);
            }
            startHeight = endWidth + 1;
            buffer.clear();
            for(int i = startHeight;i<byteFile.size()-1;i++) {
                if (flagHeight) {
                    if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                        buffer.push_back(byteFile.at(i));
                        heightFound = true;
                    }
                    if (((byteFile.at(i+1) == 0x0a) || (byteFile.at(i+1) == 0x20)) && (heightFound)) {
                        endHeight = i;
                        flagHeight = false;
                    }
                }
            }
            for(int i = 0;i<buffer.size();i++) {
                this->height = this->height * 10;
                this->height = this->height + (buffer.at(i) - 48);
            }
            startData = endHeight + 1;
            buffer.clear();
            counter = 0;
            for(int i = startData;i<byteFile.size();i++) {
                if ((byteFile.at(i) == '0') || (byteFile.at(i) == '1')) {
                    buffer.push_back(byteFile.at(i));
                    counter++;
                    if (counter == this->getWidth()) {
                        counter = 0;
                        bufferCitra.push_back(buffer);
                        buffer.clear();
                    }
                }
            }
            this->kanal.push_back(bufferCitra);

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

void Citra::printKanal(int pos) {
    if (this->kanal.size() > pos) {
        for(int i = 0; i < this->getHeight(); i++) {
            for(int j = 0; j < this->getWidth(); j++) {
                std::cout << kanal.at(pos).at(i).at(j) << " ";
            }
            std::cout << "\n";
        }
    }
}

unsigned long long Citra::getWidth() {
    return this->width;
}

unsigned long long Citra::getHeight() {
    return this->height;
}