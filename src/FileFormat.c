#include <sys/types.h>
#include <stdio.h>
#include "FileFormat.h"

void printFormat(unsigned char *buffer, const char * filename) {
  if (((buffer[0] == 'P') && (buffer[1] == '1')) || ((buffer[0] == 'P') && (buffer[1] == '4'))) {
    printf("PBM\n");
  } else if (((buffer[0] == 'P') && (buffer[1] == '2')) || ((buffer[0] == 'P') && (buffer[1] == '5'))){
    printf("PGM\n");
  } else if(((buffer[0] == 'P') && (buffer[1] == '3')) || ((buffer[0] == 'P') && (buffer[1] == '6'))) {
    printf("PPM\n");
  } else if((buffer[0] == 'B') && (buffer[1] == 'M')) {
    printf("BMP\n");
  } else {
    printf("RAW\n");
  }
}