#include <iostream>
#include <string>

#include "Console.h"
#include "File.h"
#include "Citra.h"

void Console::main() {
    std::string command = "";
    File file1;
    Citra citra1;

    std::string filename = "";
    int selected = 0;
    do {
        std::cout << "Masukkan command:\n";
        std::cin >> command;
        this->setCommand(command);

        switch(this->getCommand()) {
            case 1:
                std::cout << "List files\n";
                break;
            case 2:
                std::cout << "Masukkan nama file:\n";
                std::cin >> filename;
                file1.newFile(filename);
                citra1.loadFile(file1.getByteFile(), file1.fileType());
                std::cout << "width: " << citra1.getWidth() << std::endl;
                std::cout << "height: " << citra1.getHeight() << std::endl;
                break;
            case 3:
                switch(file1.fileType()) {
                    case 1:
                        std::cout << "PBM\n";
                        break;
                    case 2:
                        std::cout << "PGM\n";
                        break;
                    case 3:
                        std::cout << "PPM\n";
                        break;
                    case 4:
                        std::cout << "BMP\n";
                        break;
                    case 0:
                    default:
                        std::cout << "RAW\n";
                        break;
                }
                break;
            case 4:
                file1.printFileSize();
                break;
            default:
                std::cout << "Unknown Command\n";
        }
        
    } while (command.compare("end"));
}

void Console::setCommand(std::string input) {
    if(input.compare("list") == 0) {
        this->commandCode = 1;
    } else if (input.compare("add") == 0) {
        this->commandCode = 2;
    } else if (input.compare("show-file-type") == 0) {
        this->commandCode = 3;
    } else if (input.compare("show-file-size") == 0) {
        this->commandCode = 4;
    } else {
        this->commandCode = 0;
    }
}

int Console::getCommand() {
    return this->commandCode;
}