#include <iostream>
#include <string>
#include <vector>

class Citra {
    private:
        std::vector<std::vector<std::vector<unsigned char>>> kanal;
        unsigned long long height, width;
    public:
        Citra();
        void loadFile(std::vector<unsigned char> byteFile, int fileType);
        void printCitra();
        void printKanal(int pos);
        unsigned long long getWidth();
        unsigned long long getHeight();
};