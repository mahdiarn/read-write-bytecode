#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Citra.h"
#include "File.h"

Citra::Citra() {
    this->width = 0;
    this->height = 0;
    this->maxValue = 0;
}

void Citra::loadFile(std::vector<unsigned char> byteFile, int fileType) {
    std::vector<unsigned char> buffer;
    std::vector<unsigned char> bufferBinary;
    std::vector<unsigned char> singleBinary(8);
    std::fill (singleBinary.begin(),singleBinary.begin()+8,'0');
    std::vector<std::vector<unsigned char>> bufferCitra;
    bool flagWidth = true;
    bool flagHeight = true;
    bool flagMax = true;
    bool widthFound = false;
    bool heightFound = false;
    bool maxFound = false;
    int startWidth = 2;
    int endWidth;
    int startHeight;
    int endHeight;
    int startData;
    int startMax;
    int endMax;
    int counter = 0;
    unsigned char tempNum;
    std::cout << "Konstruktor\n";
    std::cout << "filetype: " << fileType << std::endl;
    switch(fileType) {
        case 1:
            this->maxValue = 1;
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
                    buffer.push_back(byteFile.at(i) - '0');
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
        case 11:
            this->maxValue = 1;
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
                        endHeight = i+1;
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
            bufferBinary.clear();
            counter = 0;
            std::fill (singleBinary.begin(),singleBinary.begin()+8,'0');
            for(int i = startData;i<byteFile.size();i++) {
                for (int j = 7; j >= 0; j-- ){
                    singleBinary.at(j) = (byteFile.at(i) % 2) + '0';
                    byteFile.at(i) /= 2;
                }
                for (int j = 0;j<singleBinary.size();j++) {
                    // std::cout << singleBinary.at(j);
                    bufferBinary.push_back(singleBinary.at(j));
                }
                // std::cout << std::endl;
            }

            bufferCitra.clear();
            buffer.clear();
            for(int i = 0;i<bufferBinary.size();i++) {
                std::cout << bufferBinary.at(i);
                if((i+1)%8 == 0) {
                    std::cout << std::endl;
                }
            }
            

            // for(int i = 0;i<bufferBinary.size();i++) {
            //     if ((bufferBinary.at(i) == '0') || (bufferBinary.at(i) == '1')) {
            //         buffer.push_back(bufferBinary.at(i));
            //         counter++;
            //         if (counter == this->getWidth()) {
            //             counter = 0;
            //             bufferCitra.push_back(buffer);
            //             buffer.clear();
            //         }
            //     }
            // }
            // this->kanal.push_back(bufferCitra);
            break;
        case 2:
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
            startMax = endHeight + 1;
            buffer.clear();
            for(int i = startMax;i<byteFile.size()-1;i++) {
                if (flagMax) {
                    if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                        buffer.push_back(byteFile.at(i));
                        maxFound = true;
                    }
                    if (((byteFile.at(i+1) == 0x0a) || (byteFile.at(i+1) == 0x20)) && (maxFound)) {
                        endMax = i+1;
                        flagMax = false;
                    }
                }
            }
            for(int i = 0;i<buffer.size();i++) {
                this->maxValue = this->maxValue * 10;
                this->maxValue = this->maxValue + (buffer.at(i) - 48);
            }
            startData = endMax;
            buffer.clear();
            tempNum = 0;
            counter = 0;
            for(int i = startData;i<byteFile.size();i++) {
                if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                    tempNum *= 10;
                    tempNum += (byteFile.at(i) - '0');
                    if (i == (byteFile.size()-1)) {
                        buffer.push_back(tempNum);
                        tempNum = 0;
                        counter++;
                        if (counter == this->getWidth()) {
                            counter = 0;
                            bufferCitra.push_back(buffer);
                            buffer.clear();
                        }
                    }
                } else {
                    if ((byteFile.at(i-1) >= '0') && (byteFile.at(i-1) <= '9')) {
                        buffer.push_back(tempNum);
                        tempNum = 0;
                        counter++;
                        if (counter == this->getWidth()) {
                            counter = 0;
                            bufferCitra.push_back(buffer);
                            buffer.clear();
                        }
                    }
                }
            }
            this->kanal.push_back(bufferCitra);
            break;
        case 3:
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
            startMax = endHeight + 1;
            buffer.clear();
            for(int i = startMax;i<byteFile.size()-1;i++) {
                if (flagMax) {
                    if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                        buffer.push_back(byteFile.at(i));
                        maxFound = true;
                    }
                    if (((byteFile.at(i+1) == 0x0a) || (byteFile.at(i+1) == 0x20)) && (maxFound)) {
                        endMax = i+1;
                        flagMax = false;
                    }
                }
            }
            for(int i = 0;i<buffer.size();i++) {
                this->maxValue = this->maxValue * 10;
                this->maxValue = this->maxValue + (buffer.at(i) - 48);
            }
            startData = endMax;
            buffer.clear();
            tempNum = 0;
            counter = 0;
            for(int i = startData;i<byteFile.size();i++) {
                if ((byteFile.at(i) >= '0') && (byteFile.at(i) <= '9')) {
                    tempNum *= 10;
                    tempNum += (byteFile.at(i) - '0');
                    if (i == (byteFile.size()-1)) {
                        buffer.push_back(tempNum);
                        tempNum = 0;
                        // counter++;
                        // if (counter == this->getWidth()) {
                        //     counter = 0;
                        //     bufferCitra.push_back(buffer);
                        //     buffer.clear();
                        // }
                    }
                } else {
                    if ((byteFile.at(i-1) >= '0') && (byteFile.at(i-1) <= '9')) {
                        buffer.push_back(tempNum);
                        tempNum = 0;
                        // counter++;
                        // if (counter == this->getWidth()) {
                        //     counter = 0;
                        //     bufferCitra.push_back(buffer);
                        //     buffer.clear();
                        // }
                    }
                }
            }
            std::cout << "Panjang buffer: " << buffer.size() << std::endl;
            for (int i = 0;i<buffer.size();i++) {
                std::cout << +buffer.at(i) << " ";
            }
            this->kanal.resize(3);
            for(int j = 0;j<3;j++) {
                tempNum = 0;
                counter = 0;
                bufferCitra.clear();
                bufferCitra.resize(this->getHeight());
                for (int i = 0;i<buffer.size();i++) {
                    // std::cout << +buffer.at(i) << " ";
                    if ((i % 3 == 0) && (j==0)) {
                        bufferCitra.at(tempNum).push_back(buffer.at(i));
                        counter++;
                    } else if ((i % 3 == 1) && (j==1)) {
                        bufferCitra.at(tempNum).push_back(buffer.at(i));
                        counter++;
                    } else if ((i % 3 == 2) && (j==2)) {
                        bufferCitra.at(tempNum).push_back(buffer.at(i));
                        counter++;
                    }
                    if (counter == this->getWidth()) {
                        counter = 0;
                        tempNum++;
                    }
                }
                this->kanal.at(j) = bufferCitra;
            }
            // this->kanal.resize(3);
            // for(int i=0;i<bufferCitra.size();i++) {
            //     if (i % 3 == 0 ) {
            //         this->kanal.at(0).push_back(bufferCitra.at(i));
            //     } else if (i % 3 == 1) {
            //         this->kanal.at(1).push_back(bufferCitra.at(i));
            //     } else {
            //         this->kanal.at(2).push_back(bufferCitra.at(i));
            //     }
            // }
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
                std::cout << +kanal.at(pos).at(i).at(j) << " ";
            }
            std::cout << "\n";
        }
    }
}

void Citra::inverse() {
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                this->kanal.at(i).at(j).at(k) = this->getMaxValue() - this->kanal.at(i).at(j).at(k);
            }
        }
    }
}

void Citra::generateHistogram() {
    if (this->getKanalSize() > 0) {
        this->histogram.resize(this->getKanalSize());
        for(int i=0;i<this->histogram.size();i++) {
            this->histogram.at(i).resize(this->getMaxValue()+1);
            for(int j=0;j<this->histogram.at(i).size();j++) {
                std::fill(this->histogram.at(i).begin(),this->histogram.at(i).end(),0);
            }
        }
        std::cout << "a\n";
        for(int i=0;i<this->getKanalSize();i++) {
            for(int j = 0; j < this->getHeight(); j++) {
                for(int k = 0; k < this->getWidth(); k++) {
                    this->histogram.at(i).at(this->kanal.at(i).at(j).at(k))++;
                }
            }
        }
    }
}

void Citra::printHistogram() {
    for (int i=0;i<this->getHistogramSize();i++) {
        for(int j = 0; j < this->histogram.at(i).size(); j++) {
            std::cout << this->histogram.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
}

void Citra::minImg( Citra matriks) {
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                if (k < matriks.getWidth() && j < matriks.getHeight() && i < matriks.getHeight()){
                    int temp = (int) this->kanal.at(i).at(j).at(k);
                    temp += (int) matriks.kanal.at(i).at(j).at(k);
                    this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
                }
            }
        }
    }
}

void Citra::plusImg( Citra matriks) {
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                if (k < matriks.getWidth() && j < matriks.getHeight() && i < matriks.getHeight()){
                    int temp = (int) this->kanal.at(i).at(j).at(k);
                    temp -= (int) matriks.kanal.at(i).at(j).at(k);
                    this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
                }
            }
        }
    }
}

void Citra::andImg( Citra matriks) {
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                if (k < matriks.getWidth() && j < matriks.getHeight() && i < matriks.getHeight()){
                    this->kanal.at(i).at(j).at(k) = (unsigned char) (this->kanal.at(i).at(j).at(k) & matriks.kanal.at(i).at(j).at(k));
                }
            }
        }
    }
}

void Citra::orImg( Citra matriks) {
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                if (k < matriks.getWidth() && j < matriks.getHeight() && i < matriks.getHeight()){
                    this->kanal.at(i).at(j).at(k) = (unsigned char) (this->kanal.at(i).at(j).at(k) | matriks.kanal.at(i).at(j).at(k));
                }
            }
        }
    }
}


void Citra::brigthen(unsigned char nilai){
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                int temp = (int) this->kanal.at(i).at(j).at(k);
                temp += nilai;
                (temp > 255) ? temp = 255 : temp = temp;
                (temp < 0) ? temp = 0 : temp = temp;
                this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
            }
        }
    }
}

void Citra::darken(unsigned char nilai){
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                int temp = (int) this->kanal.at(i).at(j).at(k);
                temp -= nilai;
                (temp > 255) ? temp = 255 : temp = temp;
                (temp < 0) ? temp = 0 : temp = temp;
                this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
            }
        }
    }
}

void Citra::calibrateBrightness(unsigned char nilai){
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                int temp = (int) this->kanal.at(i).at(j).at(k);
                temp *= nilai;
                (temp > 255) ? temp = 255 : temp = temp;
                (temp < 0) ? temp = 0 : temp = temp;
                this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
            }
        }
    }
}

void Citra::normalizeBrightness(unsigned char nilai){
    for(int i=0;i<this->kanal.size();i++) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                int temp = (int) this->kanal.at(i).at(j).at(k);
                temp /= nilai;
                (temp > 255) ? temp = 255 : temp = temp;
                (temp < 0) ? temp = 0 : temp = temp;
                this->kanal.at(i).at(j).at(k) = (unsigned char)temp;
            }
        }
    }
}

void Citra::flipX() {
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int j = 0; j < this->getHeight(); j++) {
            for (int k = 0; k < this->getWidth() / 2; k++) {
                int pos = this->getWidth() - 1 - k;
                int temp = (int) this->kanal.at(i).at(j).at(k);
                this->kanal.at(i).at(j).at(k) = this->kanal.at(i).at(j).at(pos);
                this->kanal.at(i).at(j).at(pos) = (unsigned char) temp;
            }
        }
    }
}

void Citra::flipY() {
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int k = 0; k < this->getWidth(); k++) {
            for (int j = 0; j < this->getHeight() / 2; j++) {
                int pos = this->getHeight() - 1 - j;
                int temp = (int) this->kanal.at(i).at(j).at(k);
                this->kanal.at(i).at(j).at(k) = this->kanal.at(i).at(pos).at(k);
                this->kanal.at(i).at(pos).at(k) = (unsigned char) temp;
            }
        }
    }
}

void Citra::translate(unsigned char x, unsigned char y) {
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int j = 0; j < this->getHeight(); j++) {
            int tempx[this->getWidth()];
            for (int k = 0; k < this->getWidth(); k++) {
                if (k < x) {
                    tempx[k] = 0;
                } else {
                    tempx[k] = (int) this->kanal.at(i).at(j).at(k-x);
                }
            }
            for (int k = 0; k < this->getWidth(); k++) {
                this->kanal.at(i).at(j).at(k) = (unsigned char) tempx[k];
            }
        }
    }
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int k = 0; k < this->getWidth(); k++) {
            int tempy[this->getHeight()];
            for (int j = 0; j < this->getHeight(); j++) {
                if (j < y) {
                    tempy[j] = 0;
                } else {
                    tempy[j] = (int) this->kanal.at(i).at(j-y).at(k);
                }
            }
            for (int j = 0; j < this->getHeight(); j++) {
                this->kanal.at(i).at(j).at(k) = (unsigned char) tempy[j];
            }
        }
    }
}

void Citra::notOperation() {
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int k = 0; k < this->getWidth(); k++) {
            for (int j = 0; j < this->getHeight(); j++) {
                int temp = (int) !(this->kanal.at(i).at(j).at(k));
                this->kanal.at(i).at(j).at(k) = (unsigned char) temp;
            }
        }
    }
}

void Citra::convolution(unsigned char matriks[3][3]) {
    for (int i = 0; i < this->kanal.size(); i++) {
        for (int j = 0; j < this->getHeight(); j++) {
            for (int k = 0; k < this->getWidth(); k++) {
                if (k != 0 && k != this->getWidth() - 1 && j != 0 && j != this->getHeight() - 1) {
                    unsigned char temp[3][3];
                    temp[0][0] = this->kanal.at(i).at(j-1).at(k-1);
                    temp[0][1] = this->kanal.at(i).at(j-1).at(k);
                    temp[0][2] = this->kanal.at(i).at(j-1).at(k+1);
                    temp[1][0] = this->kanal.at(i).at(j).at(k-1);
                    temp[1][1] = this->kanal.at(i).at(j).at(k);
                    temp[1][2] = this->kanal.at(i).at(j).at(k+1);
                    temp[2][0] = this->kanal.at(i).at(j+1).at(k-1);
                    temp[2][1] = this->kanal.at(i).at(j+1).at(k);
                    temp[2][2] = this->kanal.at(i).at(j+1).at(k+1);

                    unsigned char sum = 0;

                    for (int y = 0; y < 3; y++) {
                        for (int x = 0; x < 3; x++) {
                            sum += (temp[y][x] * matriks[y][x]);
                        }
                    }

                    if (sum > 255) {
                        sum = 255;
                    } else if (sum < 0) {
                        sum = 0;
                    }

                    this->kanal.at(i).at(j).at(k) = sum;
                }
            }
        }
    }
}

void Citra::sharpen(unsigned char options) {
    if (options == 1) {
        unsigned char matriks[3][3];
        matriks[0][0] = -1;
        matriks[0][1] = -1;
        matriks[0][2] = -1;
        matriks[1][0] = -1;
        matriks[1][1] = 9;
        matriks[1][2] = -1;
        matriks[2][0] = -1;
        matriks[2][1] = -1;
        matriks[2][2] = -1;
        this->convolution(matriks);
    }
}

void Citra::rgbToGrayscale() {
    if (this->getKanalSize() == 3) {
        std::vector<std::vector<std::vector<unsigned char>>> kanalGrayscale;
        kanalGrayscale.push_back(this->kanal.at(0));
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                kanalGrayscale.at(0).at(j).at(k) = (unsigned char)((this->kanal.at(0).at(j).at(k) * 0.21)+(this->kanal.at(1).at(j).at(k) * 0.72)+(this->kanal.at(2).at(j).at(k) * 0.07));
            }
        }
        this->kanal = kanalGrayscale;
    }
}

void Citra::grayscaleToBinary() {
    if (this->getKanalSize() == 1) {
        for(int j = 0; j < this->getHeight(); j++) {
            for(int k = 0; k < this->getWidth(); k++) {
                (this->kanal.at(0).at(j).at(k) <= 127) ? this->kanal.at(0).at(j).at(k) = 0 : this->kanal.at(0).at(j).at(k) = 0;
            }
        }
        this->maxValue = 1;
    }
}

unsigned long long Citra::getWidth() {
    return this->width;
}

unsigned long long Citra::getHeight() {
    return this->height;
}

unsigned int Citra::getMaxValue() {
    return this->maxValue;
}

unsigned int Citra::getKanalSize() {
    return (unsigned int)this->kanal.size();
}

unsigned int Citra::getHistogramSize() {
    return (unsigned int)this->histogram.size();
}