#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>

#include "Console.h"
#include "File.h"


int main(int argc, char **argv)
{
    Console console;
    console.main();
    // File file1("../examples/lena_gray.bmp");
    // file1.printBytes();
    // file1.printFileType();
    return 0;
}