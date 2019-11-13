#include <iostream>
#include <string>
#include <vector>

class Console {
    private:
        std::vector<std::string> commands;
        std::string command;
        int commandCode;
    public:
        void main();
        void setCommand(std::string input);
        int getCommand();
}; 