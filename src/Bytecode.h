#ifndef BYTECODE_H_INCLUDED
#define BYTECODE_H_INCLUDED
#include <sys/types.h>
/* ^^ these are the include guards */

/* Prototypes for the functions */

off_t fsize(const char *filename);
unsigned char *read_file(const char * filename);
void save_file(const char * filename1,const char * filename2, unsigned char *buffer);
void printBuffer(unsigned char *buffer, const char * filename);

#endif