#include <iostream>
#include <string>
#include <vector>

class File {
    private:
        std::vector<unsigned char> byteFile;
    public:
        File();
        File(std::string filename);
        void printBytes(bool numeric = false);
        int fileType();
        void newFile(std::string filename);
}; 