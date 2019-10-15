#include <iostream>
#include <string>

#include "Console.h"
#include "File.h"

void Console::main() {
    std::string command = "";
    File file1;
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
                break;
            case 3:
                file1.printFileType();
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
    } else {
        this->commandCode = 0;
    }
}

int Console::getCommand() {
    return this->commandCode;
}