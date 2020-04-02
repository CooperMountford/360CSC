#ifndef DISK_HEADER
#define DISK_HEADER
#include <stdio.h>
#include <stdlib.h>

void writeBlock(FILE* disk, int block, char* data);
void readBlock(FILE* disk, int block, char* buff);
void InitLLFS();

#endif