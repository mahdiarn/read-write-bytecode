/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "Bytecode.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>


off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}

unsigned char *read_file(const char * filename) {
  FILE *fptr;
  unsigned char *buffer;
  buffer = (unsigned char*)malloc ( (__intmax_t)fsize(filename) * sizeof (unsigned char));
  if ((fptr = fopen(filename,"rb")) == NULL){
      printf("Error! opening file");
      // Program exits if the file pointer returns NULL.
      exit(1);
  }
  
  fread(buffer,(__intmax_t)fsize(filename),1,fptr);
  
  fclose(fptr); 
  return buffer;
}

void save_file(const char * filename1,const char * filename2, unsigned char *buffer) {
  FILE *fptr;
  if((fptr = fopen(filename2,"wb")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
   }
   

   fwrite(buffer,(__intmax_t)fsize(filename1),1,fptr);
   fclose(fptr); 
}

void printBuffer(unsigned char *buffer, const char * filename) {
  int count = 0;
  for(int i = 0; i<(__intmax_t)fsize(filename); i++){
    
    if(buffer[i] < 16) {
      printf("0%x", buffer[i]);
    } else {
      printf("%x", buffer[i]);
    }
    printf(" ");

    if (count == 7) {
      printf(" ");
    } 
    if (count == 15) {
      printf("\n");
      count = 0;
    } else {
      count = count + 1;
    }
   }
}