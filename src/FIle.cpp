#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

#include "File.h"

File::File() {

}

File::File(std::string filename) {
    std::streampos size;
    char * memblock;
    std::ifstream myfile;
    myfile.open (filename, std::ios::binary); 
    if (myfile.is_open()) {
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(myfile), {});
        this->byteFile = buffer;
    } else std::cout << "Unable to open file";
}

void File::printBytes (bool numeric) {
    if (numeric) {
        std::vector<unsigned char>::iterator ptr; 
        for (ptr = this->byteFile.begin(); ptr < this->byteFile.end(); ptr++) 
            std::cout << std::dec << +*ptr << " "; 
    } else {
        std::vector<unsigned char>::iterator ptr; 
        for (ptr = this->byteFile.begin(); ptr < this->byteFile.end(); ptr++) 
            std::cout << std::dec << *ptr << " "; 
    }
}

int File::fileType() {
    std::vector<unsigned char>::iterator ptr; 
    if (((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '1')) || ((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '4'))) {
        return 1;
    } else if (((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '2')) || ((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '5'))){
        return 2;
    } else if(((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '3')) || ((this->byteFile.at(0) == 'P') && (this->byteFile.at(1) == '6'))) {
        return 3;
    } else if((this->byteFile.at(0) == 'B') && (this->byteFile.at(1) == 'M')) {
        return 4;
    } else {
        return 0;
    }
}

void File::newFile(std::string filename) {
    std::streampos size;
    char * memblock;
    std::ifstream myfile;
    myfile.open (filename, std::ios::binary); 
    if (myfile.is_open()) {
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(myfile), {});
        this->byteFile = buffer;
    } else std::cout << "Unable to open file";
}