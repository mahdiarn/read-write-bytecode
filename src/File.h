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
        void printFileType();
        void newFile(std::string filename);
}; 