#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "Bytecode.h"

int main(int argc, char **argv)
{
    unsigned char *buffer;
    buffer = read_file(argv[1]);

    save_file(argv[1], argv[2], buffer);
   
   return 0;
}